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

#include <cstdio>   // for FILE structures

namespace AiksaurusImpl
{
    class FileArray
    {
        private:

        // Forbid copying and assignment.
            FileArray(const FileArray& rhs);
            FileArray& operator=(const FileArray& rhs);
        
        // Data Members    
            mutable FILE* d_file;    // file pointer to read from
            const int d_structsize;  // bytes per each structure
            int d_bytes;             // total bytes in file
       
        public:

        // Exception Classes
            class OpenException {};
            class ReadException {};
            
        // Creation and Destruction
            FileArray(const char* file, int structsize) 
                throw(OpenException, ReadException);
            
            ~FileArray() throw();    

            
        // Inspection
            int getFileSize() const throw();   // bytes in file
            int getStructSize() const throw(); // bytes in structure
            int getSize() const throw();       // structs in file
           

        // Read structure at position 'position' into buf.  buf must be large
        // enough to store getStructSize() bytes.
            void read(int position, unsigned char* buf) const 
                throw(ReadException);
    };
}

#endif // INCLUDED_FILEARRAY_H

