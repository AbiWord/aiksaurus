#include "Aiksaurus.h"
#include "AsciiCompare.h"
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
        cout << "Nearby words: " << endl;
        for(const char* r = A.similar(); r[0] != 0; r = A.similar())
        {
            cout << "\t" << r << endl;
        }
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

                string option1(r);
                string option2(A.next(meaning));
                
                if ( AiksaurusImpl::AsciiCompare( option1.c_str(), argv[1] ) == 0 )
                    cout << "### " << option2 << endl;
                else
                    cout << "### " << option1 << endl;   
                
                prev_meaning = meaning;
                
                r = A.next(meaning);
                if (r[0] == 0)
                    break;
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
