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

#ifndef INCLUDED_WORDSFILE_H
#define INCLUDED_WORDSFILE_H

#include <cstdio>
#include "AiksaurusException.h"

namespace AiksaurusImpl
{
	class WordsFile
	{
	  private:

		        // No copying or assignment allowed.
		            WordsFile(const WordsFile& rhs);
		            WordsFile& operator=(const WordsFile& rhs);
		        
		        // Static information about our datafile.
		            static const int s_offsetModulus;
		            static const int s_offsetData[];
		            static const int s_numLines;
		            static const int s_maxWordLength;
		            static const int s_maxLinks;
		   
		        // File pointer to the datafile itself.
		            FILE* d_file_ptr;
		            
		        // Storage for loading each word.
		            char *d_word;
		            int *d_links;       
		          
		        // Helper functions for file i/o   
		            void _readWord(); 
		            
		        public:
		        // Creation and Destruction
		            WordsFile(const char* fname);
		            ~WordsFile();
		        
		        // Word Lookup        
		            void loadWord(int id);
		            bool findWord(const char* str, int& index);
		
		        // Inspection  
		            int getSize() const;
		            const char* getWord() const;
		            const int* getLinks() const;
		            
		        // Constants
		            static int maxWordLength();    
    };

}

#endif							// INCLUDED_WORDSFILE_H
