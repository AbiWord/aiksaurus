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

#include "WordsFile.h"
#include "FileArray.h"
#include <cassert>
#include <string>
#include <new>


const int AiksaurusImpl::WordsFile::s_maxwords = 17;

const int AiksaurusImpl::WordsFile::s_maxlinks = 5;

const int AiksaurusImpl::WordsFile::s_structsize = 
    (2 * WordsFile::s_maxlinks) + WordsFile::s_maxwords;


int AiksaurusImpl::WordsFile::maxWordLength() 
{
    return s_maxwords;
}
    
AiksaurusImpl::WordsFile::WordsFile(const char* fname)
: d_error(false),
  d_data_ptr(new FileArray(fname, s_structsize, d_error)),
  d_word(new char[s_maxwords+1]),
  d_links(new int[s_maxlinks+1])
{
    d_error = !d_error;
    d_word[0] = 0;
    d_word[s_maxwords] = 0; 
    d_links[0] = -1;
    d_links[s_maxlinks] = -1;
}
       
AiksaurusImpl::WordsFile::~WordsFile()
{
    delete d_data_ptr;
    delete d_links;
    delete d_word;
}
       
void AiksaurusImpl::WordsFile::loadWord(int id)
{
    assert(id >= 0);
    unsigned char wd[s_structsize];

    d_error = !(d_data_ptr->at(id, wd));
    
    if (d_error) 
        return;
    
    register int i = 0;
    while( i < s_maxwords )
        d_word[i] = wd[i++];

    int x = 0;
    while( i < s_structsize )
    {
        unsigned int hbyte = wd[i];
        unsigned int lbyte = wd[i+1];
        unsigned int answer = (hbyte << 8) | lbyte;
        
        if (answer == 0xFFFF)
        {
            d_links[x] = -1;
            break;
        }
        
        d_links[x++] = answer;
        i += 2;
    }
    
}

const char* 
AiksaurusImpl::WordsFile::getWord() const
{
    return d_word;
}

const int*
AiksaurusImpl::WordsFile::getLinks() const
{
    return d_links;
}


int 
AiksaurusImpl::WordsFile::findWord(const char* str)
{
    static int high_start = 
        (d_data_ptr->getBytes() / d_data_ptr->getStructSize());
        
    int low = 0, high = high_start - 1;

    std::string s(str);
    
    while(low <= high)
    {
        int mid = (high + low) / 2;
        
        loadWord(mid);
        std::string w(getWord());
        
        if (s < w)
            high = mid - 1;
        else if (s > w)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}


bool 
AiksaurusImpl::WordsFile::error() const
{
    return d_error;
}


