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

#include "FileArray.h"
#include <cassert>
#include <iostream>

FileArray::FileArray(const char* file, long structsize, bool& ok)
: d_file(fopen(file, "r")), 
  d_structsize(structsize), 
  d_bytes_cached(false)
{
    assert(d_structsize > 0);
    ok = d_file;
    cout << "ok is " << ok << endl;
}


FileArray::~FileArray()
{
    fclose(d_file);
}


long 
FileArray::getStructSize() const
{
    return d_structsize;   
}


long
FileArray::getBytes() const
{
    if (d_bytes_cached)
        return d_bytes;
    
    if (!d_file) 
        return -1;
    
    d_bytes_cached = true;
    fseek(d_file, 0L, SEEK_END);
    d_bytes = ftell(d_file);
    return d_bytes;
}


bool 
FileArray::at(long position, unsigned char* buf) const
{
    assert(position >= 0);

    if (fseek(d_file, position * d_structsize, SEEK_SET) == -1)
    {
        return false;
    }
    
    if (fread(buf, 1, d_structsize, d_file) != 
            static_cast<unsigned int>(d_structsize))
    {
        return false;
    }

    return true;
}


