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
 *
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  
 * 02111-1307, USA.
 *
 */

/*
    NOTE: this really is C code.  It only has the .cpp file extension
    because I don't know how to get automake to work correctly with 
    a mixed C++ and C program.
*/

#include "AiksaurusC.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

static char* dupeString(const char* str);
static void noMemory();
static void checkError();
static void noSynonyms();
static void printSynonyms();
static void handleArguments(int argc, char** argv);

int main(int argc, char** argv)
{
    int found;
    
    /* Check that our arguments are correct. */
    handleArguments(argc, argv); 
    
    /* Create thesaurus object.  (might cause an error...) */
    if (!Aiksaurus_init())
    {
        noMemory();
    }
    checkError();
    
    /* Search thesaurus for the word. */
    found = Aiksaurus_find(argv[1]);
    checkError();
    
    if (found)
    {
        /* synonyms were found.  print off the synonyms. */
        printSynonyms();
    }
    
    else
    {
        /* no synonyms found, print off nearby words. */
        noSynonyms();
    }

    printf("\n");
    return 0;
}

/* 
 * dupeString()
 *  create a copy of a string.  this copy must be destroyed
 *  by the caller with free().
 */
static char* dupeString(const char* str)
{
    char* ret = (char*) malloc ( strlen(str) * sizeof(char) + 1 );
    
    if (!ret)
        noMemory();
    
    strcpy(ret, str);
    return ret;
}

    
/* 
 * noMemory()
 * we set this as our new handler so that if we run out of 
 * memory, we can just print an error message and die.
 */
static void noMemory()
{
    printf("Error: Virtual memory exhausted.\n");
    exit(1);
}


/*    
 * checkError() 
 *  checks to see if there was an error with the thesaurus, 
 *  prints the message and terminates the program if there is.
 */    
static void checkError()
{
    if (Aiksaurus_error()[0])
    {
        printf("%s\n", Aiksaurus_error());
        exit(1);
    }
}


/*
 * noSynonyms()
 *  called if there are no known synonyms.  prints out nearby
 *  words.
 */
static void noSynonyms()
{
    const char* r;
    
    checkError();

    printf("*** No synonyms known. ***\n");
    printf("Alphabetically similar known words are: \n");

    for(r = Aiksaurus_similar(); r[0]; r = Aiksaurus_similar())
    {
        checkError();
        printf("\t%s\n", r);
    }
}


/*
 * printSynonyms()
 *  called if there are known synonyms.  prints out all the 
 *  meanings that the thesaurus knows.
 */
static void printSynonyms()
{   
    const char* r;
    int prev_meaning = -1;
    int meaning;
    
    for(r = Aiksaurus_next(&meaning); r[0]; r = Aiksaurus_next(&meaning))
    {
        /* next() might cause an error, ensure that it didn't. */
        checkError();
 
        /* see if we have a new meaning. */
        if (meaning != prev_meaning)
        { 
            /* we do have a new meaning.  figure out what the titles are. */
            char* option1 = dupeString(r);
            char* option2 = dupeString( Aiksaurus_next(&meaning) );
            char* title;
            int i;
            
            /* we called next() again, so check the error again. */
            checkError();                    
            
            /* choose which title to output.  we want option1 unless it's
               the same as our current word, */
            title = strcmp(option1, Aiksaurus_word()) ? (option1) : (option2);
            
            /* now we know what title we want to output.  normally we want
               to add a line of space between each meaning, but we don't
               want to do this if this is the very first meaning.  So, we
               can see if prev_meaning is -1 and respond accordingly.  */
            if (prev_meaning != -1)
            { 
                printf("\n\n");
            }
            
            /* update what our previous meaning was. */
            prev_meaning = meaning;
            
            /* Let's go ahead and actually print our title now.
               All this just prints "=== <title> ===================" */
            printf("=== %s ", title);
            for(i = strlen(title); i < 25; ++i) { printf("="); }
            printf("\n");            
            
            r = Aiksaurus_next(&meaning);
            checkError();

            if (!r[0])
                break;
        }

        else
        {
            /* this is a continuation of the previous meaning.
               print a comma to separate this word from the last. */
            printf(", ");
        }

        /* Output the actual synonym. */
        printf("%s", r);
    }

    /* This just looks a bit better. */
    printf("\n");
}


/*
 * handleArguments()
 *  checks for --version or --help flags, and ensures 
 *  that the user searched for a word.
 */
static void handleArguments(int argc, char** argv)
{
    /* the message to print if we get --version or -v. */
    const char* version = 
        "Aiksaurus, Version " VERSION "\n"
        "Copyright (C) 2001-2002 by Jared Davis\n\n"
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
        "02111-1307, USA.\n\n";
    
    /* the message to print out if we get --help or -h */
    const char* help = 
        "Aiksaurus is an English-language thesaurus library.  This \n"
        "is a simple command-line interface to it.\n\n"
        "   -v, --version        Output version information and quit.\n"
        "   -h, --help           Output this help message and quit.\n\n"
        "For more help, visit\n"
        "   http://www.aiksaurus.com/\n\n";
    
    int i;
    
    for(i = 1;i < argc;++i)
    {
        char* arg = argv[i];
    
        /* see if we got --version. */
        if ( !strcmp(arg, "--version") || !strcmp(arg, "-v") )
        {
            printf(version);
            exit(0);
        }

        /* see if we got --help */
        else if ( !strcmp(arg, "--help") || !strcmp(arg, "-h") )
        {
            printf("Usage: %s [word]\n\n", argv[0]);
            printf(help);
            exit(0);
        }   
    }

    /* make sure we have exactly two arguments. */
    if (argc != 2)
    {
        printf("Usage: %s [word]\n", argv[0]);
        printf(help);
        exit(1);
    }
}


