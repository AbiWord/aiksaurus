#include "WordsFile.h"
#include <string>
#include <fstream>

int main()
{
    cout << "Enter input file: " << flush;
    string input; cin >> input;
 
    cout << "Enter output file: " << flush;
    string ofile; cin >> ofile;

    ofstream out(ofile.c_str());
    
    WordsFile wf(input.c_str());
    assert(!wf.error());

    for(int i = 0;!wf.error();++i)
    {
        wf.loadWord(i);
        if (wf.error())
            break;
        
        out << wf.getWord() << ' ';

        const int* links = wf.getLinks();
        for(int i = 0; links[i] != -1;++i)
           out << links[i] << " ";
        out << '\n'; 
    }

    return 0;
}
