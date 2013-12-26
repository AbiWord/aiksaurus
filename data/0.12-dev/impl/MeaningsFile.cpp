/*
 * Aiksaurus - An open source thesaurus library
 * Copyright (C) 2001 by Jared Davis
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
    // provide better performance, but this seems to work well.
    //
    static const int BUF_SIZE = 256;

    
    //
    // MeaningStream Class
    //   Purpose: read input from the Meanings file.
    //
    class MeaningStream
    {
        private:

            // No copying or assignment, please.
            MeaningStream(MeaningStream& rhs);
            MeaningStream& operator=(MeaningStream& rhs);
        
            // d_file_ptr: pointer to the meanings file stream.
            FILE* d_file_ptr;

            // d_position: our current position in our read buffer.
            int d_position;

            // d_end: the size of our read buffer.
            int d_end;

            // d_buffer: our read buffer itself.
            unsigned char d_buffer[BUF_SIZE * 2];
        
        
        public:

            // MeaningStream Constructor:
            //   Initialize d_file_ptr to the correct FILE* structure.
            //   Initialize d_position and d_end so that the stream will
            //   be read at first call to read().
            MeaningStream(FILE* file_ptr);
            
            
            // MeaningStream::read
            //   Put the next integer in the stream into x.
            //   Return true normally, false if cannot read any more.
            bool read(int& x, AiksaurusError& err);
    };
}



//
// MeaningStream Constructor
//   Store pointer to FILE structure, and tell our buffer that it is
//   empty to begin with.
//
inline
AiksaurusImpl::MeaningStream::MeaningStream(FILE* file_ptr)
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
AiksaurusImpl::MeaningStream::read(int& x, AiksaurusError& err)
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
            err.setDescription(AiksaurusError::CORRUPT_MEANINGS_FILE);
            ret = false;
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
AiksaurusImpl::MeaningsFile::MeaningsFile(const char* fname)
    : d_file_ptr(fopen(fname, "r"))
{
    if (!d_file_ptr)
    {
        d_error.setDescription(AiksaurusError::CANNOT_OPEN_MEANINGS_FILE);
        return;
    }
}


//
// MeaningsFile Destructor
//   Close our file if we were able to open it successfully.
//
AiksaurusImpl::MeaningsFile::~MeaningsFile()
{
    if (d_file_ptr)
        fclose(d_file_ptr);
}


//
// _readline()
//   Reads an entire line from the meanings file into an array.
//   Observe that the array must have enough space to hold the 
//   line, plus one slot for end-of-links (-1).
//
int
AiksaurusImpl::MeaningsFile::_readline(MeaningStream& s, int* buffer) 
{
    int i = 0;
    int x;

    while(s.read(x, d_error))
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
AiksaurusImpl::MeaningsFile::getWords(int id)
{   
    // First we need to create our buffer to return.
    // We know that there are at most s_dataMaxLineLength
    // bytes on any given line.  However, since each link
    // is composed of two bytes, we only need half this 
    // in order to store everything we need.

    // TO DO: why doesn't this have a +1 at the end?
    static int buffer[s_dataMaxLineLength / 2];

    // If we have not successfully opened a file, we need to go ahead
    // and just return nothing here. 
    if (!d_file_ptr)
    {
        buffer[0] = -1;
        return buffer;
    }
        
    
    // Divide by our offset modulus to get the start of the 
    // correct partition.  
    long partition_start = id / s_offsetModulus;

    // Jump to the offset pointed to by our partition.
    if (fseek(d_file_ptr, s_offsetData[partition_start], SEEK_SET) != 0)
    {
        // There was an error jumping to that part of the file.
        // Set an error and return an empty list of links.
        d_error.setDescription(AiksaurusError::CORRUPT_MEANINGS_FILE);
        buffer[0] = -1;
        return buffer;
    }

    // Create a MeaningStream to read the file.
    MeaningStream s(d_file_ptr);

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


//
// getError()
//   Simple function to just return the AiksaurusError object that we
//   are using to report errors.
//
const AiksaurusImpl::AiksaurusError&
AiksaurusImpl::MeaningsFile::getError() const
{
    return d_error;
}


