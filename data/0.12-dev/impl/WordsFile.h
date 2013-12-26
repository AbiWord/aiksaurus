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

//
// WordsFile Class
//
//   This class is a low level interface to the Words File itself.
//
//   It provides a convenient interface to the FileArray class that
//   it is implemented through, and all the error checking that a
//   nuclear engineer could want. 
//
//   Basic operations are:
//     
//      loadWord(i) - load a particular word by index.
//      getWord() - figure out what word was just loaded.
//      getLinks() - get the links that the word had.
//      findWord(str) - binary search file to find the word.
//

#include "AiksaurusErrors.h"   // Error reporting mechanism.

namespace AiksaurusImpl
{
    // Forward Declarations
    class FileArray;
    class AiksaurusError; 

    class WordsFile
    {
        private:

        // No copying or assignment allowed.
            WordsFile(const WordsFile& rhs);
            WordsFile& operator=(const WordsFile& rhs);
        
        // Information about maximum word size, link size.
            static const int s_maxwords;
            static const int s_maxlinks;
            static const int s_structsize;
   
        // Reference to Errors object. 
            AiksaurusError d_error;
    
        // Pointer to a file array, accesses the data.       
            FileArray* d_data_ptr;

        // Number of words that are in the Words file.
            int d_size;

        // Storage for arrays when doing word lookups.
            char *d_word;
            int *d_links;       
           
            
        public:

        // Creation and Destruction
            WordsFile(const char* fname);
            ~WordsFile();
        
        // Word Lookup        
            bool loadWord(int id);
            int findWord(const char* str);

        // Inspection  
            int getSize() const;
            const char* getWord() const;
            const int* getLinks() const;
            const AiksaurusError& getError() const; 
            
        // Constants
            static int maxWordLength();    
    };

}
    
#endif // INCLUDED_WORDSFILE_H

