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

#include "FileArray.h"  // Header we're implementing.
#include <cassert>      

namespace AiksaurusImpl
{
    
    FileArray::FileArray(const char* file, int structsize) 
    throw(OpenException, ReadException)
        : d_structsize(structsize) 
    {
        // Structures must have _some_ size to them.
        assert(d_structsize > 0);
       
        // Attempt to open the file.  Throw an exception if not successful.
        d_file = fopen(file, "r"); 
        if (!d_file)
            throw OpenException();

        // Figure out how large the file is.  Throw an exception if not 
        // successful.
        fseek(d_file, 0L, SEEK_END);
        d_bytes = ftell(d_file);
        if (!d_bytes)
            throw ReadException();
    }


    FileArray::~FileArray() throw()
    {
        // close the file since we're done with it.
        fclose(d_file);
    }


    //
    // getStructSize()
    //   Returns the size of each structure in bytes.
    //
    int FileArray::getStructSize() const throw()
    {
        return d_structsize;   
    }


    //
    // getFileSize()
    //   Returns the size of the file in bytes. 
    //
    int FileArray::getFileSize() const throw()
    {
        return d_bytes;
    }


    //
    // getSize()
    //   Returns the number of structures in the file.
    //
    int FileArray::getSize() const throw()
    {
        return d_bytes / d_structsize;
    }
    

    //
    // FileArray::read
    //   Return the element at a particular position.  
    //   No bounds checking is done.  
    //
    void 
    FileArray::read(int position, unsigned char* buf) const throw(ReadException)
    {
        assert(position >= 0);
        assert(position < getSize());
    
        if (fseek(d_file, position * getStructSize(), SEEK_SET) == -1)
        {
            // Unable to jump to the right part of the file.
            throw ReadException();
        }   
    
        if (fread(buf, 1, getStructSize(), d_file) != 
                static_cast<unsigned int>(getStructSize()))
        {
            // unable to read d_structsize bytes from file.
            throw ReadException();
        }
    }
    
}
