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

#include "..\..\core\src\Aiksaurus.h"
#include "..\..\core\src\AsciiCompare.h"
#include "..\..\core\src\config.h"
#include <iostream>
#include <string>
using namespace std;
using AiksaurusImpl::AsciiCompare;

const char* copyright = 
    "This program is free software; you can redistribute it and/or\n"
    "modify it under the terms of the GNU General Public License\n"
    "as published by the Free Software Foundation; either version 2\n"
    "of the License, or (at your option) any later version.\n\n"
    "This program is distributed in the hope that it will be useful,\n"
    "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "GNU General Public License for more details.\n\n"
    "You should have received a copy of the GNU General Public License\n"
    "along with this program; if not, write to the Free Software\n"
    "Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  \n"
    "02111-1307, USA.\n";

    
const char* help = 
    "Aiksaurus is an English-language thesaurus library.  This \n"
    "is a simple command-line interface to it.\n\n"
    "   -v, --version        Output version information and quit.\n"
    "   -h, --help           Output this help message and quit.\n\n"
    "For more help, visit\n"
    "   http://www.aiksaurus.com/\n";

    
static void checkError(const Aiksaurus& A)
{
    if (A.error()[0])
    {
        cerr << A.error() << endl;
        exit(1);
    }
}


static void noSynonyms(Aiksaurus& A)
{
    checkError(A);
    cout << "*** No synonyms known. ***" << endl;
    cout << "Alphabetically similar known words are: " << endl;
    for(const char* r = A.similar(); r[0] != 0; r = A.similar())
    {
        checkError(A);
        cout << "\t" << r << endl;
    }
}


static void printSynonyms(Aiksaurus& A)
{
    int prev_meaning = -1;
    int meaning;
    
    for(const char* r = A.next(meaning); r[0]; r = A.next(meaning))
    {
        checkError(A);
 
        if (meaning != prev_meaning) // new meaning.
        {
            string option1(r); // title option 1
            string option2(A.next(meaning));  // title option 2
            checkError(A);                    
            
            if (prev_meaning != -1) 
                cout << "\n\n";
            prev_meaning = meaning;
            
            // output title of meaning.  choose option 2 if 
            // the user searched for option 1, option 1 
            // otherwise.
            string& title = AsciiCompare(option1.c_str(), A.word())
                    ? (option1) 
                    : (option2);
            
            cout << "=== " << title << ' ';

            for(int i = title.size(); i < 25; ++i)
                cout << '=';
           
            cout << endl;
            
            r = A.next(meaning);
            checkError(A);

            if (r[0] == 0)
                break;
        }

        else
            cout << ", ";

        cout << r;
    }

    cout << endl;
}


int main(int argc, const char** argv)
{
    for(int i = 1;i < argc;++i)
    {
        string arg(argv[i]);
    
        if ((arg == "--version") || (arg == "-v"))
        {
            cout << "Aiksaurus, Version " << VERSION << "\n"
                 << "Copyright (C) 2001 by Jared Davis.\n\n"
                 << copyright << "\n";
            exit(0);
        }

        else if ((arg == "--help") || (arg == "-h"))
        {
            cout << "Usage: " << argv[0] << " [word]\n\n"
                 << help << "\n";
            exit(0);
        }   
    }
    
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << "[word]\n"
             << help;
        exit(1);
    }
    
    Aiksaurus A;
    checkError(A);
    
    if (!A.find(argv[1]))
        noSynonyms(A);
    else
        printSynonyms(A);

    cout << endl;
    
    return 0;
}

