#include "fast.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    AikSaurusFAST f;

    while(1)
    {
        cout << "\nword to find: " << flush;
        string word; cin >> word;

        const vector<string>& syns = f.getSynonyms(word);

        copy(syns.begin(), syns.end(), ostream_iterator<string>(cout, ", "));
    }
    
    return 0;
}
