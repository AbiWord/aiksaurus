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

#ifndef INCLUDED_FILEARRAY_H
#define INCLUDED_FILEARRAY_H

//
// FileArray Class
//
//   Treats a file as an array using standard C-style FILE* pointers,
//   fseek, and so forth.  Pretty basic, and does some basic error 
//   handling stuff.
//

#include <cstdio>

namespace AiksaurusImpl
{
    class FileArray
    {
        private:

        // Prevent copying and assignment.
            FileArray(const FileArray& rhs);
            FileArray& operator=(const FileArray& rhs);
        
        // Pointer to an ANSI-C file structure    
            mutable FILE* d_file;
        
        // Size of structures held by the file.    
            const long d_structsize;

        // File size in bytes.    
            mutable bool d_bytes_cached;
            mutable long d_bytes;
       
        public:

        // Creation/Destruction
            FileArray(const char* file, long structsize, bool& ok);
            ~FileArray();    

            
        // Inspection - Bytes in file, structure size.
            long getBytes() const;
            long getStructSize() const;        

            
        // This is the indexing of sorts.  Retrieves element at 
        // position, and stores it in buf.  Buf must be big enough
        // to hold structsize bytes.  
            bool at(long position, unsigned char* buf) const;
    };
}

#endif // INCLUDED_FILEARRAY_H

