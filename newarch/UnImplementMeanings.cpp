#include "MeaningStream.h"
#include "Arguments.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, const char** argv)
{
    Arguments a(argc, argv);
    
    string wf, mf;
    a.get("--wordsfile", wf, "");
    a.get("--meanings", mf, "");

    if ((wf == "") || (mf == ""))
    {
        cerr << "Usage: " << argv[0] << " --wordsfile=[file] --meanings=[file]" << endl;
        return 1;
    }
    
    ifstream win(wf.c_str());
    vector<string> words;
    words.reserve(30000);
    while(win >> wf)
        words.push_back(wf);
    
    ifstream in(mf.c_str());
    MeaningStream s(in);

    int x;
    while(s >> x)
    {
        if (x == MeaningStream::EOL)
            cout << endl;

        else
            cout << words[x] << ' ';
    }

    return 0;
}
