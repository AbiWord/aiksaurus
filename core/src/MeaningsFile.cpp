/*
 * Aiksaurus - An english-language thesaurus library
 * Copyright (C) 2001-2002 by Jared Davis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 *
 */

#include "MeaningsFile.h"
#include "MeaningsHash.h"


//////////////////////////////////////////////////////////////////////////
//
//  MeaningStream Class 
//
//////////////////////////////////////////////////////////////////////////

namespace AiksaurusImpl 
{
    
    //
    // BUF_SIZE: number of links to read from the meanings file 
    // per read.  Note: will read (BUF_SIZE * 2) bytes per read
    // since each link is 2 bytes long.
    //
    // This constant is completely arbitrary.  Other values may 
    // provide better performance, but I haven't tested for this 
    // since 256 seems to work well enough.
    //
    static const int BUF_SIZE = 256;

    
    //
    // MeaningStream Class
    //   Purpose: read input from the Meanings file.
    //
    class MeaningStream
    {
        private:

            // Prevent copying, assignment.
            MeaningStream(MeaningStream& rhs);
            MeaningStream& operator=(MeaningStream& rhs);
            
            unsigned char d_buffer[BUF_SIZE * 2]; // read buffer
            FILE* d_file_ptr;  // file we read from
            int d_position;    // current pos in read buffer
            int d_end;         // size of read buffer

            
        public:

            // MeaningStream Constructor:
            //   Initialize d_file_ptr to the correct FILE* structure.
            //   Initialize d_position and d_end so that the stream will
            //   be read at first call to read().
            MeaningStream(FILE* file_ptr) throw();
           

            // MeaningStream::read
            //   Put the next integer in the stream into x.
            //   Return true normally, false if EOF.
            bool read(int& x) throw(AiksaurusException);
    };


//
// MeaningStream Constructor
//   Store pointer to FILE structure, and tell our buffer that it is
//   empty to begin with.
//
inline
MeaningStream::MeaningStream(FILE* file_ptr) throw()
    : d_file_ptr(file_ptr), 
      d_position(0), 
      d_end(0)
{           
    
}


//
// MeaningStream Read Function
//
//   Read a single link from the meaning stream.  We actually read
//   chunks of the file at a time, and then return pieces of those
//   chunks.
//
//   Returns TRUE if able to read a link, FALSE if unable to read 
//   a link. (EOF or problem reading file).
//
inline bool 
MeaningStream::read(int& x) throw(AiksaurusException)
{
    bool ret = true;
    
    // If position is less than end, there is still some buffer left
    // that we can read from.  We want to read the next two bytes 
    // from the buffer into x.
    if (d_position < d_end)
    {
        x = d_buffer[d_position++] << 8;
        x |= d_buffer[d_position++];
    }

    // Otherwise, we have reached the end of our buffer.  We need
    // to read a new buffer in.
    else
    {
        // Attempt to read BUF_SIZE * 2 bytes from the file.
        d_end = fread(d_buffer, 1, BUF_SIZE * 2, d_file_ptr);

        // Make sure there weren't any errors reading from the
        // file.  We don't want to continue if there was an error.
        if (ferror(d_file_ptr))
        {
            throw AiksaurusException(
                    AiksaurusException::CORRUPT_MEANINGS_FILE
            );
        }
        
        // If we were able to read data, go ahead and reset 
        // position to 0 and we read two bytes as above.
        else if (d_end) 
        {
            d_position = 0;
            x = d_buffer[d_position++] << 8;
            x |= d_buffer[d_position++];
        }
        
        // Otherwise, we were unable to read anything more.  
        // We've most likely reached the end of file.  Return 
        // false to indicate failure.
        else 
        {
            ret = false;
        }
    }

    return ret;
}


//////////////////////////////////////////////////////////////////////////
//
//  MeaningsFile Class Implementation
//
//////////////////////////////////////////////////////////////////////////

//
// MeaningsFile Constructor
//   All we need to do is get a handle to the file. 
//   We'll also check to make sure our meanings file opens ok.
//
MeaningsFile::MeaningsFile(const char* fname) throw(AiksaurusException)
{
    d_file_ptr = fopen(fname, "r");
    if (!d_file_ptr)
    {
        throw AiksaurusException(
                AiksaurusException::CANNOT_OPEN_MEANINGS_FILE
        );
    }
}


//
// MeaningsFile Destructor
//   Close the meanings file because we're done reading it.
//
MeaningsFile::~MeaningsFile() throw()
{
    fclose(d_file_ptr);
}


//
// _readline()
//   Reads an entire line from the meanings file into an array.
//   Observe that the array must have enough space to hold the 
//   line, plus one slot for end-of-links (-1).
//
int
MeaningsFile::_readline(MeaningStream& s, int* buffer) throw(AiksaurusException) 
{
    int i = 0;

    int x;
    while(s.read(x)) // might throw an AiksaurusException.
    {
        if (x == 0xFFFF)  // 0xFFFF is the end-of-line marker.
            break;
       
        buffer[i++] = x;
    }
   
    buffer[i] = -1;  // we terminate with -1 to say end of links.
    
    return i;
}


//
// getWords()
//
//   Return array of all links in a particular meaning set.
//   The array will be terminated with -1 at the end so you 
//   will know where to stop.
//
//   NOTE:  This array is only valid until the next time 
//   the function is called.
//
int* 
MeaningsFile::getWords(int id) throw(AiksaurusException)
{   
    // First we need to create our buffer to return.
    // We know that there are at most s_dataMaxLineLength
    // bytes on any given line.  However, since each link
    // is composed of two bytes, we only need half this 
    // in order to store everything we need.

    // TO DO: why doesn't this have a +1 at the end?
    static int buffer[s_dataMaxLineLength / 2];

    // Divide by our offset modulus to get the start of the 
    // correct partition.  
    long partition_start = id / s_offsetModulus;

    // Jump to the offset pointed to by our partition.
    if (fseek(d_file_ptr, s_offsetData[partition_start], SEEK_SET) != 0)
    {
        throw AiksaurusException(
                AiksaurusException::CORRUPT_MEANINGS_FILE
        );
    }

    // Create a MeaningStream to read the file.
    MeaningStream s(d_file_ptr);

    // TO DO: Take a long, hard look at this loop.
    
    // Read until we get the correct line.
    int line = partition_start * s_offsetModulus;
    for(; line <= id; line++)
    {
        if (!_readline(s, buffer))
        {
            // we failed to read the correct lines. 
            // return an empty set of words.
            buffer[0] = -1;
            break;
        }
    }

    return buffer;
}


}
