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

#include "WordsFile.h"         // Header we're implementing.
#include "FileArray.h"         // Basis of words file.
#include "AsciiCompare.h"      // For AsciiCompare function.
#include <cassert>             // We like assert().
#include <new>                 // Needed for "nothrow" option.

namespace AiksaurusImpl
{
    
//////////////////////////////////////////////////////////////////////////
//
//  Static Data 
//
//////////////////////////////////////////////////////////////////////////

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
static inline void 
strReplace(char* str, char a, char b) throw()
{
    for(register unsigned int i = 0; str[i] != 0; ++i)
    {
        if (str[i] == a)
            str[i] = b;
    }
}


//
// s_wordlen
//   maximum length of a word in the thesaurus.
//   this is the size of a buffer that you need to allocate to 
//   guarantee that you can hold a word.
//
const int WordsFile::s_wordlen = 17;


//
// s_maxlinks
//   maximum number of links a word can have.  
//   this is the size of an array you need to allocate to 
//   guarantee you can hold all the links a word has.
//
const int WordsFile::s_maxlinks = 5;


// 
// s_structsize
//   the size of a words structure is one byte for every 
//   letter a word can have (i.e., s_wordslen), plus two
//   bytes for every link it has (i.e. 2 * s_maxlinks)
//
const int WordsFile::s_structsize = 
    (2 * WordsFile::s_maxlinks) + WordsFile::s_wordlen;

    
//
// maxWordLength()
//   static function to return maximum length of any word.
//   just returns s_wordlen to the user.
//
int 
WordsFile::maxWordLength() throw()
{
    return s_wordlen;
}
    


//////////////////////////////////////////////////////////////////////////
//
//  Creation and Destruction
//
//////////////////////////////////////////////////////////////////////////


//
// WordsFile Constructor
//   Attempt to safely initialize the Words file.  Might have problems
//   with running out of memory or file not found.
//
WordsFile::WordsFile(const char* fname) throw(AiksaurusException)
{
    try
    {
        d_data_ptr = new FileArray(fname, s_structsize);
        d_word = new char[s_wordlen + 1];
        d_links = new int[s_maxlinks + 1];
    
        // initialize current word, links to be empty.  
        d_word[0] = 0;
        d_links[0] = -1;
    
        // set last position of word, links to be terminating.
        // since we know there are at most s_wordlen characters 
        // in a word, and at most s_maxlinks links per word, we
        // know that these values will never be overwritten, 
        // which means we can just define them now.    
        d_word[s_wordlen] = 0; 
        d_links[s_maxlinks] = -1;
    }
    
    catch(std::bad_alloc)
    {
        throw AiksaurusException(
                AiksaurusException::CANNOT_ALLOCATE_MEMORY
        );
    }
    
    catch(FileArray::OpenException)
    {
        throw AiksaurusException(
                AiksaurusException::CANNOT_OPEN_WORDS_FILE
        );
    }

    catch(FileArray::ReadException)
    {
        throw AiksaurusException(
                AiksaurusException::CORRUPT_WORDS_FILE
        );
    }
}


// 
// WordsFile Destructor
//
WordsFile::~WordsFile() throw()
{
    delete d_data_ptr;
    delete d_links;
    delete d_word;
}
       



//////////////////////////////////////////////////////////////////////////
//
//  Inspection Routines
//
//////////////////////////////////////////////////////////////////////////

//
// getWord()
//   Return the word that was read in the last successful call to 
//   loadWord().  If loadWord failed, then this will just be the 
//   last requested word that succeeded, or the empty string if no
//   calls to loadWord() were ever successful.
//
const char* 
WordsFile::getWord() const throw()
{
    return d_word;
}


//
// getLinks()
//   Return the links associated with the last loaded word.  As with 
//   getWord(), this will return the last successful results or an
//   empty list if there were no successful loads.
//
const int*
WordsFile::getLinks() const throw()
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
    return d_data_ptr->getSize();
}



//////////////////////////////////////////////////////////////////////////
//
//  Manipulation
//
//////////////////////////////////////////////////////////////////////////

//
// loadWord()
//   Read a particular word from the Words file. 
//
void WordsFile::loadWord(int id) throw(AiksaurusException)
{
    // Ensure that we are within bounds.
    assert(id >= 0);
    assert(id < getSize());
    
    // Create a buffer to read the word into.  We will read
    // the entire size of a structure. 
    unsigned char buffer[s_structsize];
   
    try
    {
        // Read the word into our buffer.
        d_data_ptr->read(id, buffer); 
    }
    
    catch(FileArray::ReadException)
    {
        throw AiksaurusException(
                AiksaurusException::CORRUPT_WORDS_FILE
        );
    }
    
    // Read the actual word part of this word into our d_word
    // buffer.  We only want the first s_wordlen bytes for the 
    // actual text.
    int i = 0;
    while(i < s_wordlen)
    {
        d_word[i] = buffer[i++];
    }
   
    // Now that we've read the word, we want to read the links
    // themselves.  x will count to tell us what numbered link
    // we are reading.
    int x = 0;
    while(i < s_structsize)
    {
        // join the next two bytes.
        unsigned int link = (buffer[i] << 8) | buffer[i+1];
        
        // The constant 0xFFFF is used to denote that no more
        // links are present.  If we run into it, set this link
        // to -1 and stop processing.  Recall that we don't 
        // need to handle the case where all available links are 
        // present, because we put a -1 at the one-past-the-end
        // slot in the constructor and this never gets overwritten.
        if (link == 0xFFFF)
        {
            d_links[x] = -1;
            break;
        }
        
        // Otherwise set this link to the answer and advance 
        // to read the next two bytes.
        d_links[x++] = link;
        i += 2;
    }
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
    char s[s_wordlen + 2];          
    s[s_wordlen + 1] = 0;               
    for(int i = 0; i < (s_wordlen + 2); ++i)
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


}
