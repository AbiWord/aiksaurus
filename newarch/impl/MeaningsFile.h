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

#ifndef INCLUDED_MEANINGSFILE_H
#define INCLUDED_MEANINGSFILE_H

#include <cstdio>

namespace AiksaurusImpl {

class MeaningStream;
class MeaningsFile
{
    private:

    // Offset information for hash structure.
        static const int s_offsetModulus;
        static const int s_offsetData[];
        static const int s_dataMaxLineLength;
        
    // No copying or assignment allowed.
        MeaningsFile(const MeaningsFile& rhs);
        MeaningsFile& operator=(const MeaningsFile& rhs);
        
    // Any error is a problem with the file.
        bool d_error;
    
    // Pointer to the actual meanings file.
        mutable FILE* d_file_ptr;

        int readline(MeaningStream& s, int* buffer) const;
        
    public:

    // Creation and Destruction
        MeaningsFile(const char* fname);
        ~MeaningsFile();
        
    // Word Lookup        
        int* getWords(int id) const;

    // Error Checking
        bool error() const;
};

}

#endif // INCLUDED_MEANINGSFILE_H

