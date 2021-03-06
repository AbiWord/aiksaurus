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

#ifndef INCLUDED_WORDSFILE_H
#define INCLUDED_WORDSFILE_H

class FileArray;

class WordsFile
{
    private:

    // No copying or assignment allowed.
        WordsFile(const WordsFile& rhs);
        WordsFile& operator=(const WordsFile& rhs);
        
    // Information about maximum word size, link size.
        static const int s_maxword;
        static const int s_maxlinks;
    
    // Pointer to a file array, accesses the data.       
        FileArray* d_data_ptr;
        
    // Any error is a problem with the file.
        bool d_error;
       
        
    public:

    // Creation and Destruction
        WordsFile(const char* fname);
        ~WordsFile();
        
    // Word Lookup        
        int findWord(const char* str);

    // Word/Links Retrieval   
        void loadWord(int id);
        const char* getWord() const;
        const int* getLinks() const;

    // Error Checking
        bool error() const;
};

#endif // INCLUDED_WORDSFILE_H

