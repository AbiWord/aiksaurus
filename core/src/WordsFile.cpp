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

#include "WordsFile.h"        
#include "WordsHash.h"
#include "AsciiCompare.h"     

#include <cassert>             
#include <new>


namespace AiksaurusImpl
{

//
// ASCII_SPACE and ASCII_COLON
//   In the data file, spaces are stored as colons.  We use these 
//   constants (rather than using ':' and ' ' in place) to convert 
//   between them so that on a machine with a strange (non-ascii) 
//   character set, we should still be able to perform the conversions 
//   correctly.
//
static const int ASCII_SPACE = 32;
static const int ASCII_COLON = 58;


//
// strReplace
//   Simple function to replace all instances of one letter in a 
//   string with another letter.
//
static inline void strReplace(char* str, char a, char b) throw()
{
    for(;*str;++str)
    {
        if (*str == a) 
            *str = b;
    }
}


//
// maxWordLength()
//   static function to return maximum length of any word.
//   just returns s_wordlen to the user.
//
int WordsFile::maxWordLength() throw()
{
    return s_maxWordLength;
}
    

//
// getWord()
//   Return the word that was read in the last successful call to 
//   loadWord().  If loadWord failed, then this will just be the 
//   last requested word that succeeded, or the empty string if no
//   calls to loadWord() were ever successful.
//
const char* WordsFile::getWord() const throw()
{
//    strReplace(d_word, ASCII_COLON, ASCII_SPACE);
    return d_word;
}


//
// getLinks()
//   Return the links associated with the last loaded word.  As with 
//   getWord(), this will return the last successful results or an
//   empty list if there were no successful loads.
//
const int* WordsFile::getLinks() const throw()
{
    return d_links;
}


//
// getSize()
//   Return the size of the words file (number of entries).  When you
//   ask to load words, they should be in the range [0, getSize).  In 
//   other words, getSize() - 1 is the last entry.
//
int 
AiksaurusImpl::WordsFile::getSize() const throw()
{
    return s_numLines;
}


//
// WordsFile Constructor
//   Attempt to safely initialize the Words file.  Might have problems
//   with running out of memory or file not found.
//
WordsFile::WordsFile(const char* fname) throw(AiksaurusException)
{
    
    try
    {
        d_word = 0;
        d_links = 0;
        
        d_word = new char[maxWordLength() + 1];
        d_links = new int[s_maxLinks + 1];
        d_file_ptr = fopen(fname, "r");

        if (!d_file_ptr)
        {
            delete[] d_word;
            delete[] d_links;
            throw AiksaurusException(AiksaurusException::CANNOT_OPEN_WORDS_FILE);
        }
    }
    
    catch(std::bad_alloc)
    {
        delete[] d_word;
        delete[] d_links;
        throw AiksaurusException(AiksaurusException::CANNOT_ALLOCATE_MEMORY);
    }

    
    d_word[0] = 0;    // initialize current word to be empty on creation. 
    d_links[0] = -1;  // initialize links to be empty on creation.
    
    
    // set last position of word, links to be terminating.
    // these values will never be overwritten, so this just 
    // makes the load code more convenient.    
    d_word[maxWordLength()] = 0; 
    d_links[s_maxLinks] = -1;
}


// 
// WordsFile Destructor
//   Free up our memory and be sure to close the file.
//
WordsFile::~WordsFile() throw()
{
    delete[] d_links;
    delete[] d_word;

    fclose(d_file_ptr);
}
       

//
// findWord()
//   Search for a character string using a binary search.
//   Returns the index of the word on success, or -1 on 
//   failure.
//
bool WordsFile::findWord(const char* str, int& index) throw(AiksaurusException)
{  
    // Create copy of str, so that we can turn spaces into colons.
    // We only need to copy the first s_wordlen + 1 bytes to ensure
    // that we will get a correct match.
    char s[maxWordLength() + 2];          
    s[maxWordLength() + 1] = 0;               
    for(int i = 0; i < (maxWordLength() + 2); ++i)
    {
        s[i] = str[i];
        if (!str[i]) break;
    } 
   
    // In the datafile, spaces are stored as colons.  Convert spaces
    // on search word into colons so that we can do a simple case 
    // insensitive compare. 
    strReplace(s, ASCII_SPACE, ASCII_COLON);
    
    // Initialize low/high for classic binary search.   
    int low = 0, high = getSize() - 1;    
    index = -1;
    
    // Perform our binary search.
    while(low <= high)
    {
        int mid = (high + low) / 2;
        
        loadWord(mid);
        
        int compare = AsciiCompare(s, d_word);
        
        if (compare < 0) 
            high = mid - 1;
        
        else if (compare > 0)
            low = mid + 1;
        
        else {
            index = mid;
            break;
        }
    }

    bool ret = true;
    
    if (index == -1)
    { 
        index = low;
        return false;
    }
    
    return ret;
}


//
// _readWord()
//   Read a single word from the file, loading the word into d_word and 
//   loading the links into d_links.
//
void WordsFile::_readWord()
{
    // First we will read in a word.
    for(int i = 0; i <= maxWordLength(); ++i)
    {
        int c = fgetc(d_file_ptr);

        if (ferror(d_file_ptr) || feof(d_file_ptr)) 
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);
       
        if (!c) {
            d_word[i] = 0;
            break;
        }

        else
            d_word[i] = c;
    }

    
    // Now we want to read links.
    for(int i = 0; ;++i)
    {
        int x1 = fgetc(d_file_ptr), 
            x2 = fgetc(d_file_ptr);

        if (ferror(d_file_ptr) || feof(d_file_ptr)) 
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);
      
        if ((x1 == 0xFF) && (x2 == 0xFF))
        {
            d_links[i] = -1; 
            break;
        }

        else if (i > s_maxLinks)
            throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);
        
        d_links[i] = (x1 << 8) | x2;
    }
}


//
// loadWord()
//   Read a particular word from the Words file. 
//
void WordsFile::loadWord(int id) throw(AiksaurusException)
{
    assert(id >= 0);
    assert(id < getSize());
   
    long partition_start = id / s_offsetModulus;
    if (fseek(d_file_ptr, s_offsetData[partition_start], SEEK_SET) != 0)
    {
        throw AiksaurusException(AiksaurusException::CORRUPT_WORDS_FILE);
    }   

    int line = partition_start * s_offsetModulus;
    for(; line <= id; ++line)
    {
        _readWord();
    }
}





}
