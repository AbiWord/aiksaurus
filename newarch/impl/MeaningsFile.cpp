/*
 * AikSaurus - An open source thesaurus library
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
#include <iostream>
#include <string>


// BUF_SIZE: number of links to read from the meanings file 
// per read.  Note: will read (BUF_SIZE * 2) bytes per read
// since each link is 2 bytes long.
static const int BUF_SIZE = 256;


// MeaningStream Class: Efficiently reads from a Meanings file
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
        MeaningStream(FILE* file_ptr)
        : d_file_ptr(file_ptr), d_position(0), d_end(0)
        {
            
        }
                
        // MeaningStream::read
        //   Put the next integer in the stream into x.
        //   Return true normally, false if cannot read any more.
        //   SHOULD BE INLINE.
        bool read(int& x)
        {
            bool ret = true;
    
            if (d_position < d_end)
            {
                x = d_buffer[d_position++] << 8;
                x |= d_buffer[d_position++];
            }

            else
            {
                d_end = fread(d_buffer, 1, BUF_SIZE * 2, d_file_ptr);

                if (d_end) 
                {
                    d_position = 0;
                    x = d_buffer[d_position++] << 8;
                    x |= d_buffer[d_position++];
                }
        
                else
                {
                    ret = false;
                }
            }

            return ret;
        }
};








MeaningsFile::MeaningsFile(const char* fname)
: d_error(false)
{
    d_file_ptr = fopen(fname, "r");

    if (!d_file_ptr)
        d_error = true;
}


MeaningsFile::~MeaningsFile()
{
    if (d_file_ptr)
        fclose(d_file_ptr);
}


int
MeaningsFile::readline(MeaningStream& s, int* buffer) const
{
    int i = 0;
    int x;

    while(s.read(x))
    {
        if (x == 0xFFFF)
            break;
       
        buffer[i++] = x;
    }
   
    buffer[i] = -1;
    return i;
}


int* 
MeaningsFile::getWords(int id) const
{  
    static int buffer[s_dataMaxLineLength / 2];
   
    long partition_start = id / s_offsetModulus;
    fseek(d_file_ptr, s_offsetData[partition_start], SEEK_SET);

    MeaningStream s(d_file_ptr);

    int line = partition_start * s_offsetModulus;
    for(; line <= id; line++)
    {
        if (!readline(s, buffer))
            break;
    }

    return (line == id + 1) ? (buffer) : (NULL);
}


bool
MeaningsFile::error() const
{
    return d_error;
}


