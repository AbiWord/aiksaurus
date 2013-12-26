#include "WordsFile.h"
#include <string>
#include <fstream>

using namespace AiksaurusImpl;
int main()
{
    cout << "Enter input file: " << flush;
    string input; cin >> input;
 
    cout << "Enter output file: " << flush;
    string ofile; cin >> ofile;

    ofstream out(ofile.c_str());
   
    WordsFile wf(input.c_str());

    if (wf.getError().isError())
    {
        cerr << wf.getError().getDescription() << endl;
        return 1;
    }
    
    for(int i = 0;i < wf.getSize();++i)
    {
        wf.loadWord(i);

        if (wf.getError().isError())
        {
            cerr << wf.getError().getDescription() << endl;
            return 1;
        }
        
        out << wf.getWord() << ' ';

        const int* links = wf.getLinks();
        for(int i = 0; links[i] != -1;++i)
           out << links[i] << " ";
        out << '\n'; 
    }

    return 0;
}
