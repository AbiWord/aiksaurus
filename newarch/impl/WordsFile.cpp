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
#include <new>

const int WordsFile::s_maxwords = 17;

const int WordsFile::s_maxlinks = 5;

const int WordsFile::s_structsize = 
    (2 * WordsFile::s_maxlinks) + WordsFile::s_maxwords;


WordsFile::WordsFile(const char* fname)
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
       
WordsFile::~WordsFile()
{
    delete d_data_ptr;
    delete d_links;
    delete d_word;
}
       
void WordsFile::loadWord(int id)
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
WordsFile::getWord() const
{
    return d_word;
}

const int*
WordsFile::getLinks() const
{
    return d_links;
}


int 
WordsFile::findWord(const char* str)
{
    return 0;
}


bool 
WordsFile::error() const
{
    return d_error;
}


