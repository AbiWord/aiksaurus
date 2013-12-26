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

#include <cstdio>
#include <cassert>
#include <iostream>
#include <strstream>
#include "Arguments.h"
using namespace std;


static const int BUF_SIZE = 256;

class MeaningStream
{
    private:

        FILE* d_file_ptr;
        int d_position;
        int d_end;
        unsigned char d_buffer[BUF_SIZE * 2];
        
    public:

        MeaningStream(FILE* file_ptr);
        bool read(int& x);
};

MeaningStream::MeaningStream(FILE* file_ptr)
: d_file_ptr(file_ptr), d_position(0), d_end(0)
{
}


bool MeaningStream::read(int& x)
{
    bool ret = true;
    
    if (d_position < d_end)
    {
        x = d_buffer[d_position++] << 8;
        x |= d_buffer[d_position++];
    }

    else
    {
        d_end = fread(d_buffer, 1, BUF_SIZE * 2, d_file_ptr);

        if (d_end) 
        {
            d_position = 0;
            x = d_buffer[d_position++] << 8;
            x |= d_buffer[d_position++];
        }
        
        else
        {
            ret = false;
        }
    }

    return ret;
}



const char* copyright =
"/*\n"
" * Aiksaurus - An open source thesaurus library\n"
" * Copyright (C) 2001 by Jared Davis\n"
" *\n"
" * This program is free software; you can redistribute it and/or\n"
" * modify it under the terms of the GNU General Public License\n"
" * as published by the Free Software Foundation; either version 2\n"
" * of the License, or (at your option) any later version.\n"
" *\n"
" * This program is distributed in the hope that it will be useful,\n"
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
" * GNU General Public License for more details.\n"
" *\n"
" * You should have received a copy of the GNU General Public License\n"
" * along with this program; if not, write to the Free Software\n"
" * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA\n"
" * 02111-1307, USA.\n"
" *\n"
" */\n\n";

const char* autogen = 
"/*\n"
" * This file is automatically generated by the MkOffsetTable \n"
" * program.  It should not be necessary to modify this file by \n"
" * hand.  Please see the MkOffsetTable program for more info.\n"
" *\n"
" */\n\n";


int main(int argc, const char** argv)
{
    Arguments A(argc, argv);
    int split_size;
    string infile;
    A.get("--split", split_size, 10);
    A.get("--input", infile, "");

    FILE* in = fopen(infile.c_str(), "r");
    
    MeaningStream s(in);
    
    cout << copyright << autogen << endl;
    
    cout << "const int AiksaurusImpl::MeaningsFile::s_offsetModulus = " << split_size << ";\n\n";
    
    cout << "const int AiksaurusImpl::MeaningsFile::s_offsetData[] = \n{\n";
      
    cout << "\t0,\t // 0 lines\n";
    
    int lines_read = 0;
    int bytes_read = 0;
    int max_line_length = 0;
    int this_line_length = 0;

    int x;
    while(s.read(x))
    {
        bytes_read += 2;
        this_line_length += 2;

        if (x == 0xFFFF)
        {   
            lines_read++;
            
            if (this_line_length > max_line_length)
                max_line_length = this_line_length;
            
            this_line_length = 0;
            
            if ((lines_read % split_size) == 0)
            {
                cout << "\t" << bytes_read << "," 
                     << "\t // " << lines_read << " lines\n";
            }
        }
    }

    cout << "};\n\n";
    
    cout << "const int AiksaurusImpl::MeaningsFile::s_dataMaxLineLength = " 
         << max_line_length << ";\n\n";
    
    cout << "\n// total bytes read: " << bytes_read << endl;
    
    return 0;
}





