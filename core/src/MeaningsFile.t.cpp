#include "MeaningsFile.h"
#include "Arguments.h"
#include "WordsFile.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
using namespace AiksaurusImpl;
int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    string wfile; 
    string mfile;
    string ofile;
    A.get("-m", mfile, "meanings.dat");
    A.get("-w", wfile, "words.dat");
    A.get("-o", ofile, "mrec.45");

    try
    {    
        MeaningsFile mf(mfile.c_str());
        WordsFile wf(wfile.c_str());
    
        ofstream fout(ofile.c_str());

        for(int n = 0; ;++n)
        {
            int* words = mf.getWords(n);
            if (words[0] == -1)
                break;
       
            for(int i = 0;words[i] != -1;++i)
            {
                wf.loadWord(words[i]);
                fout << wf.getWord() << ' ';
            }
        
            fout << endl;
        }
    }
    
    catch(AiksaurusException& e)
    {
        cerr << e.getDescription() << endl;
    }

    return 0;
}
