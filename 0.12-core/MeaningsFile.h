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
#include "AiksaurusException.h"

namespace AiksaurusImpl 
{
    class MeaningStream;
    class MeaningsFile
    {
        private:

            // No copying or assignment allowed.
            MeaningsFile(const MeaningsFile& rhs);
            MeaningsFile& operator=(const MeaningsFile& rhs);
            
            // Offset information for hash structure.
            static const int s_offsetModulus;
            static const int s_offsetData[];
            static const int s_dataMaxLineLength;

            // Pointer to the actual meanings file.
            FILE* d_file_ptr;

            // Utility function
            int _readline(MeaningStream& s, int* buffer) 
                throw(AiksaurusException);
            
        public:

            // Creation and Destruction
            MeaningsFile(const char* fname) throw(AiksaurusException);
            ~MeaningsFile() throw();

            // Word Lookup        
            int* getWords(int id) throw(AiksaurusException);
    };
}

#endif // INCLUDED_MEANINGSFILE_H

