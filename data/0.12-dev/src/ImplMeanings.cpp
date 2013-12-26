#include "Arguments.h"
#include "Meanings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

const char NEWLINE[3] = { 0xFF, 0xFF, 0 };
    
int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    string mfile, wfile, ofile;
    if ( (!A.get("-m", mfile, "")) || 
         (!A.get("-w", wfile, "")) ||
         (!A.get("-o", ofile, "")) )
    {
        cerr << "Syntax: " << argv[0] << "-m=m.# -w=w.# -o=m-i.#" << endl;
        exit(1);
    }
         
    cout << "\tReading words file..." << flush;
    map<string, int> words;
    ifstream win(wfile.c_str());
    string s;
    int line = 0;
    while(win >> s) 
        words.insert(make_pair(s, line++));
    cout << " done. (" << words.size() << " words)" << endl;

    
    cout << "\tReading meanings file..." << flush;
    ifstream min(mfile.c_str());
    MeaningFamily meanings;
    extractMeaningFamily(min, meanings);
    cout << "done. (" << meanings.size() << " meanings)" << endl;


    cout << "\tCreating output file...\n" << flush;
    ofstream out(ofile.c_str());

    cout << "\t[";
    for(unsigned int i = 0;i <= meanings.size() / 100;++i)
       cout << '-';
    cout << "]" << endl; 

    cout << "\t[";
    for(unsigned int x = 0;x < meanings.size();++x)
    {
        if ((x % 100) == 0)
            cout << "*" << flush;

        const MeaningSet& ms = meanings[x];

        for(unsigned int i = 0;i < ms.size();++i)
        {
            map<string, int>::iterator word = words.find(ms[i]);
            assert(word != words.end());
            assert(word->first == ms[i]);
            
            int x = word->second;
            unsigned char out1 = static_cast<unsigned char>((x & 0xFFFF) >> 8);
            unsigned char out2 = static_cast<unsigned char>(x & 0xFF);
        
            out << out1 << out2;
        }

        out << NEWLINE;
    }    
    cout << ']';
    
    cout << endl; 
    return 0;
}
