/*
 * Aiksaurus - An English-language thesaurus library
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

#ifndef INCLUDED_MEANINGSFILE_H
#define INCLUDED_MEANINGSFILE_H

#include <cstdio>
#include "AiksaurusException.h"

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
            MeaningStream(FILE* file_ptr);
           

            // MeaningStream::read
            //   Put the next integer in the stream into x.
            //   Return true normally, false if EOF.
            bool read(int& x);
    };

    class MeaningsFile
    {
      private:

        // No copying or assignment allowed.
        MeaningsFile (const MeaningsFile & rhs);
          MeaningsFile & operator= (const MeaningsFile & rhs);

        // Offset information for hash structure.
        static const int s_offsetModulus;
        static const int s_offsetData[];
        static const int s_dataMaxLineLength;

        // Pointer to the actual meanings file.
        FILE* d_file_ptr;

            // Utility function
            int _readline(MeaningStream& s, int* buffer);
            
        public:

            // Creation and Destruction
            MeaningsFile(const char* fname);
            ~MeaningsFile();

            // Word Lookup        
            int* getWords(int id);
    };
}

#endif							// INCLUDED_MEANINGSFILE_H
