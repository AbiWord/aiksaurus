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

#ifndef INCLUDED_WORDSFILE_H
#define INCLUDED_WORDSFILE_H

#include "AiksaurusException.h"   // Error reporting mechanism.

namespace AiksaurusImpl
{
    class FileArray;
    class AiksaurusError; 

    class WordsFile
    {
        private:

        // No copying or assignment allowed.
            WordsFile(const WordsFile& rhs);
            WordsFile& operator=(const WordsFile& rhs);
        
        // Information about maximum word size, link size.
            static const int s_wordlen;
            static const int s_maxlinks;
            static const int s_structsize;
   
        // Pointer to a file array, accesses the data.       
            FileArray* d_data_ptr;

        // Storage for arrays when doing word lookups.
            char *d_word;
            int *d_links;       
           
            
        public:

        // Creation and Destruction
            WordsFile(const char* fname) throw(AiksaurusException);
            ~WordsFile() throw();
        
        // Word Lookup        
            void loadWord(int id) throw(AiksaurusException);
            bool findWord(const char* str, int& index) throw(AiksaurusException);

        // Inspection  
            int getSize() const throw();
            const char* getWord() const throw();
            const int* getLinks() const throw();
            
        // Constants
            static int maxWordLength() throw();    
    };

}
    
#endif // INCLUDED_WORDSFILE_H

