#include "Aiksaurus.h"
#include <iostream>
#include <string>
using namespace std;


int main()
{
    Aiksaurus A;

    while(1)
    {
        cout << "\n\nSearch for word: " << flush;
        string word; cin >> word;

        if (!A.find(word.c_str()))
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
                    cout << "\nMeaning " << meaning << "\n";
                    prev_meaning = meaning;
                }

                cout << r << ", ";
            }
        }
    }

    return 0;
}
