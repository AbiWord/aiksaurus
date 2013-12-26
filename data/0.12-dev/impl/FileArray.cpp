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

#include "FileArray.h"
#include <cassert>

AiksaurusImpl::FileArray::FileArray(const char* file, long structsize, bool& ok)
    : d_file(fopen(file, "r")), 
      d_structsize(structsize), 
      d_bytes_cached(false)
{
    assert(d_structsize > 0);
    ok = (d_file != 0);
}


AiksaurusImpl::FileArray::~FileArray()
{
    // close the file if it's still open.
    if (d_file != 0)
        fclose(d_file);
}


//
// getStructSize()
//    Just return the structsize as was specified in the constructor.
//    The user really should know what this is on their own.
//
long 
AiksaurusImpl::FileArray::getStructSize() const
{
    return d_structsize;   
}


//
// getBytes()
//   Returns the size of the file (if able to calculate this).
//   Returns -1 if unable to calculate the file's size.
//
long
AiksaurusImpl::FileArray::getBytes() const
{
    // return cached answer if available.
    if (d_bytes_cached) return d_bytes;
    
    // return failure if file was unable to be opened.
    if (!d_file) return -1;
    
    // otherwise, answer not cached yet.  mark that we
    // will cache this answer.
    d_bytes_cached = true;

    // jump to the end of the file.
    fseek(d_file, 0L, SEEK_END);

    // figure out where we're at.  ftell() might return -1
    // on failure, which is fine because that's what we 
    // return on failure too.
    d_bytes = ftell(d_file);
    
    return d_bytes;
}



//
// FileArray::at
//   Return the element at a particular position.  
//   No bounds checking is done.  
//
bool 
AiksaurusImpl::FileArray::at(long position, unsigned char* buf) const
{
    assert(position >= 0);

    // ensure file is open before we start trying to read from it.
    if (!d_file)
    {
        return false;
    }
    
    // Jump to the right position in the file.
    if (fseek(d_file, position * d_structsize, SEEK_SET) == -1)
    {
        return false;
    }
    
    // Read structsize bytes from the file.
    if (fread(buf, 1, d_structsize, d_file) != 
            static_cast<unsigned int>(d_structsize))
    {
        return false;
    }

    return true;
}


