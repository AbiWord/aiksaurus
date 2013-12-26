#include "Aiksaurus.h"
#include <iostream>
#include <string>
using namespace std;


int main(int argc, const char** argv)
{
    if (argc != 2)
    {
        cout << "Syntax: " << argv[0] << " [word]" << endl;
        exit(1);
    }

    Aiksaurus A;
    
    if (!A.find(argv[1]))
    {
        cout << "*** No synonyms known. ***" << endl;
    }

    else
    {
        int prev_meaning = -1;
        int meaning;
        for(const char* r = A.next(meaning); r[0] != 0; r = A.next(meaning))
        {
            if (meaning != prev_meaning)
            {
                if (prev_meaning != -1)
                    cout << "\n\n";
                        
                cout << "# Meaning " << meaning << "\n";
                prev_meaning = meaning;
            }
            else
            {
                cout << ", ";
            }

            cout << r;
        }

        cout << endl;
    }

    return 0;
}
