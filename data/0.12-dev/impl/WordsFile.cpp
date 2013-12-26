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
#include <cassert>             // We like assert().
#include <cstring>             // strcmp useful for binary search.
#include <new>                 // Needed for "nothrow" option.


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
strReplace(char* str, char a, char b)
{
    for(register unsigned int i = 0; str[i] != 0; ++i)
    {
        if (str[i] == a)
            str[i] = b;
    }
}


//
// s_maxwords
//   maximum length of a word in the thesaurus.
//   this is the size of a buffer that you need to allocate to 
//   guarantee that you can hold a word.
//
const int AiksaurusImpl::WordsFile::s_maxwords = 17;


//
// s_maxlinks
//   maximum number of links a word can have.  
//   this is the size of an array you need to allocate to 
//   guarantee you can hold all the links a word has.
//
const int AiksaurusImpl::WordsFile::s_maxlinks = 5;


// 
// s_structsize
//   the size of a words structure is one byte for every 
//   letter a word can have (i.e., s_maxwords), plus two
//   bytes for every link it has (i.e. 2 * s_maxlinks)
//
const int AiksaurusImpl::WordsFile::s_structsize = 
    (2 * WordsFile::s_maxlinks) + WordsFile::s_maxwords;

    
//
// maxWordLength()
//   static function to return maximum length of any word.
//   just returns s_maxwords to the user.
//
int 
AiksaurusImpl::WordsFile::maxWordLength() 
{
    return s_maxwords;
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
AiksaurusImpl::WordsFile::WordsFile(const char* fname)
{
    bool ok;
    d_data_ptr = new(std::nothrow) FileArray(fname, s_structsize, ok);
    d_word = new(std::nothrow) char[s_maxwords + 1];
    d_links = new(std::nothrow) int[s_maxlinks + 1];
    
    // Ensure that all of our memory allocations succeeded.
    if (!d_data_ptr || !d_word || !d_links)
    {
        d_error.setDescription(AiksaurusError::CANNOT_ALLOCATE_MEMORY);
        return;
    }
    
    // Ensure that the words file was opened successfully.
    if (!ok)
    {
        d_error.setDescription(AiksaurusError::CANNOT_OPEN_WORDS_FILE);
        return;
    }
    
    // Initialize the size of the words file.  This is just the amount
    // of bytes in the file, divided by the structure's size.
    long bytes = d_data_ptr->getBytes();
    if (bytes == -1)
    {
        d_error.setDescription(AiksaurusError::CORRUPT_WORDS_FILE);
        return;
    }
    
    else
    {
        assert( d_data_ptr->getStructSize() != 0 );
        d_size = bytes / d_data_ptr->getStructSize();
    }
    
    // initialize current word, links to be empty.  
    d_word[0] = 0;
    d_links[0] = -1;
    
    // set last position of word, links to be terminating.
    // since we know there are at most s_maxwords characters 
    // in a word, and at most s_maxlinks links per word, we
    // know that these values will never be overwritten, 
    // which means we can just define them now.    
    d_word[s_maxwords] = 0; 
    d_links[s_maxlinks] = -1;
}


// 
// WordsFile Destructor
//
AiksaurusImpl::WordsFile::~WordsFile()
{
    // This is safe, because if the memory allocations fail,
    // then these will get set to 0, and it's always safe to 
    // delete a null pointer.
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
AiksaurusImpl::WordsFile::getWord() const
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
AiksaurusImpl::WordsFile::getLinks() const
{
    return d_links;
}


//
// getError()
//   Return the AiksaurusError object associated with this Words file.
//   This should be const since nothing needs to change on it.
//
const AiksaurusImpl::AiksaurusError& 
AiksaurusImpl::WordsFile::getError() const
{
    return d_error;
}


//
// getSize()
//   Return the size of the words file (number of entries).  When you
//   ask to load words, they should be in the range [0, getSize).  In 
//   other words, getSize() - 1 is the last entry.
//
int 
AiksaurusImpl::WordsFile::getSize() const
{
    return d_size;
}



//////////////////////////////////////////////////////////////////////////
//
//  Manipulation
//
//////////////////////////////////////////////////////////////////////////

//
// loadWord()
//   Read a particular word from the Words file. 
//   Return TRUE on success, FALSE on failure.
//
bool AiksaurusImpl::WordsFile::loadWord(int id)
{
    // Ensure that we are within bounds.
    assert( (id >= 0) && (id < d_size) );
    
    // Create a buffer to read the word into.  We will read
    // the entire size of a structure. 
    unsigned char wd[s_structsize];

    
    // Try to read the given word, fail if we can't.
    if (!d_data_ptr->at(id, wd))
    {
        d_error.setDescription(AiksaurusError::CORRUPT_WORDS_FILE);
        return false;
    }
    
    
    // Read the actual word part of this word into our d_word
    // buffer.  We only want the first s_maxwords bytes for the 
    // actual text.
    int i = 0;
    while(i < s_maxwords)
    {
        d_word[i] = wd[i++];
    }

    
    // Now that we've read the word, we want to read the links
    // themselves.  x will count to tell us what numbered link
    // we are reading.
    int x = 0;
    while(i < s_structsize)
    {
        // join the next two bytes.
        unsigned int answer = (wd[i] << 8) | wd[i+1];
        
        // The constant 0xFFFF is used to denote that no more
        // links are present.  If we run into it, set this link
        // to -1 and stop processing.  Recall that we don't 
        // need to handle the case where all available links are 
        // present, because we put a -1 at the one-past-the-end
        // slot in the constructor and this never gets overwritten.
        if (answer == 0xFFFF)
        {
            d_links[x] = -1;
            break;
        }
        
        // Otherwise set this link to the answer and advance 
        // to read the next two bytes.
        d_links[x++] = answer;
        i += 2;
    }

    // If we got this far, we did allright.
    return true;
}


//
// findWord()
//   Search for a character string using a binary search.
//   Returns the index of the word on success, or -1 on 
//   failure.
//
int 
AiksaurusImpl::WordsFile::findWord(const char* str)
{   
    // Convert word to use colons instead of spaces.
    char* s = const_cast<char*>(str);
    strReplace(s, ASCII_SPACE, ASCII_COLON);
    
    // Initialize low/high for classic binary search.   
    int low = 0, high = d_size - 1;    
    
    // Return value to use.  Initialize to be -1 for failure.
    int ret = -1;
    
    // Perform our binary search.
    while(low <= high)
    {
        int mid = (high + low) / 2;
        
        // Load the word at position 'mid'
        loadWord(mid);
        
        // Compare this word with our search word.
        int compare = strcasecmp(s, d_word);
        
        if (compare < 0) 
        {
            high = mid - 1;
        }
        
        else if (compare > 0)
        {
            low = mid + 1;
        }
        
        else
        {
            ret = mid;
            break;
        }
    }

    // Restore string to its original form since we 
    // really weren't supposed to change it.
    strReplace(s, ASCII_COLON, ASCII_SPACE);

    // Return what we've found.
    return ret;
}

