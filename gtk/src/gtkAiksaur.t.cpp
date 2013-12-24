/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
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
 */

#include <AiksaurusGTK.h>
#include "config.h"
#include <stdlib.h>
#include <gtk/gtk.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    const char* description = 
        "Aiksaurus is an English-language thesuarus library.  This\n"
        "is a graphical interface to it.\n\n"
        "   -v, --version      Output version information and quit.\n"
        "   -h, --help         Output this help message and quit.\n\n"
        "For more information, visit\n"
        "   http://www.aiksaurus.com/\n\n";
    
    const char* license =
        "AiksaurusGTK, Version " VERSION "\n" 
        "Copyright (C) 2001 by Jared Davis.\n\n"
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
        "Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA\n"
        "02111-1307, USA.\n\n";
   
    const char* opening = 
        "Welcome to AiksaurusGTK, Version " VERSION "\n"
        "    http://www.aiksaurus.com/\n\n"
        
        "To find synonyms for a word, enter the word into the \"look\n"
        "up\" box above.\n\n"
        
        "Command line arguments are:\n"
        "   --help, -h      Displays a help message, then exits.\n"
        "   --version, -v  Displays version and license, then exits.\n\n"   

        "Also, you can send a word as an argument to this program \n"
        "to skip this screen and jump right to that word.";
    
	gtk_init(&argc, &argv);
  
    for(int i = 1;i < argc;++i)
    {
        string s(argv[i]);
        if ((s == "--help") || (s == "-h"))
        {
            cout << "Usage: " << argv[0] << " [word]\n\n" << description;
            exit(0);
        }
        else if ((s == "--version") || (s == "-v"))
        {
            cout << license;            
            exit(0);
        }
    }
   
    const char* search = (argc > 1) ? (argv[argc-1]) : (0);
    
    AiksaurusGTK thesaurus; 
    thesaurus.setTitle("AiksaurusGTK");
    thesaurus.setInitialMessage(opening);
    thesaurus.hideReplacebar();
    thesaurus.runThesaurus(search);
    
	return 0;
};
