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

    string file; 
    A.get("-m", file, "m-i.45");
    MeaningsFile mf(file.c_str());
    A.get("-w", file, "w-i.45");
    WordsFile wf(file.c_str());
    assert(!wf.error());
    A.get("-o", file, "mrec.45");
    ofstream fout(file.c_str());

    for(int n = 0; ;++n)
    {
        int* words = mf.getWords(n);
        if (!words)
            break;
       
//        cout << "(" << n << "): ";
        
        for(int i = 0;words[i] != -1;++i)
        {
//            cout << words[i] << ' ';
            wf.loadWord(words[i]);
            if (wf.error())
            {
//                cout << "\n\nError: words[i] is " << words[i] << endl;
                return 0;
            }

            fout << wf.getWord() << ' ';
        }
        fout << endl;
    }

    return 0;
}
