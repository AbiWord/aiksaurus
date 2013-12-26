#include "Meanings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

const char* message = 
    "This program converts a meanings (words) file into a meanings \n"
    "implementation file.  It requires a meanings file (m.#) and an \n"
    "associated words file (w.#).  \n";

const char NEWLINE[3] = { 0xFF, 0xFF, 0 };
    
int main()
{
    cout << message << endl;
    
    
    cout << "Name of Meanings file (m.#): " << flush;
    string mfile; cin >> mfile;

    cout << "Name of Words file (w.#): " << flush;
    string wfile; cin >> wfile;

    cout << "Name of Output file: (m-itxt.#): " << flush;
    string ofile; cin >> ofile;
    
    
    cout << "Reading words file..." << flush;
    map<string, int> words;
    ifstream win(wfile.c_str());
    string s;
    int line = 0;
    while(win >> s) 
        words.insert(make_pair(s, line++));
    cout << " done. (" << words.size() << " words)" << endl;

    
    cout << "Reading meanings file..." << flush;
    ifstream min(mfile.c_str());
    MeaningFamily meanings;
    extractMeaningFamily(min, meanings);
    cout << "done. (" << meanings.size() << " meanings)" << endl;


    cout << "Creating output file...\n" << flush;
    ofstream out(ofile.c_str());

    cout << "[";
    for(unsigned int i = 0;i <= meanings.size() / 100;++i)
       cout << '-';
    cout << "]" << endl; 

    cout << '[';
    for(unsigned int x = 0;x < meanings.size();++x)
    {
        if ((x % 100) == 0)
            cout << "*" << flush;

        const MeaningSet& ms = meanings[x];

        for(unsigned int i = 0;i < ms.size();++i)
        {
            map<string, int>::iterator word = words.find(ms[i]);
            assert(word != words.end());
            
            int x = word->second;
            out << x << ' ';
        }

        out << endl;
    }    
    cout << ']';
    
    cout << endl; 
    return 0;
}
