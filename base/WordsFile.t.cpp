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

    try
    {   
        WordsFile wf(input.c_str());

        for(int i = 0;i < wf.getSize();++i)
        {
            wf.loadWord(i);
    
            out << i << "  " << wf.getWord() << ' ';

            const int* links = wf.getLinks();
            for(int i = 0; links[i] != -1;++i)
               out << links[i] << " ";
            out << '\n'; 
        }   
    }
    catch(AiksaurusException& e)
    {
        cout << e.getDescription() << endl;
        return 1;
    }

    return 0;
}
