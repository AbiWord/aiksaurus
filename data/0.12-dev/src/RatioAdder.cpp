#include "Meanings.h"
#include "Ratios.h"
#include "FastSaurus.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <strstream>
#include <map>
#include <iterator>
using namespace std;

const char * message = 
    "RatioAdder Program\n"
    "This program adds mean direct link ratio (mdlr) and mean \n"
    "return link ratio (mrlr) information for each meaning set \n"
    "in an meanings file.  This is an incredibly slow operation \n"
    "and you probably don't want to apply it to large files.  \n"
    "For your convenience, the program can process only a portion \n"
    "of a meanings file.\n";

int main()
{
    cout << message << endl;
   
    cout << "Enter meanings file name (m.#): " << flush;
    string meaningsfile; cin >> meaningsfile;
   
    cout << "Enter output file name (m-r.#): " << flush;
    string outputfile; cin >> outputfile;
    
    cout << "Enter processing start line (e.g. 0): " << flush;
    int startline; cin >> startline;

    cout << "Enter number of lines to process (e.g. 100): " << flush;
    int blocksize; cin >> blocksize;

    cout << "Reading in meanings file... " << flush;
    vector<MeaningSet> meanings;
    ifstream min(meaningsfile.c_str());
    extractMeaningFamily(min, meanings);
    cout << meanings.size() << " meaning classes read." << endl;

    cout << "Creating output file... " << endl;    
    ofstream out(outputfile.c_str());
   
    unsigned int stop = startline + blocksize;
    for(unsigned int i = startline; (i < stop) && (i < meanings.size()); ++i)
    {
        const MeaningSet& meaning = meanings[i];
        
        double mdlr = meanDirectLinkRatio(meaning);
        double mrlr = meanReturnLinkRatio(meaning);
        
        out << mdlr << ' ' << mrlr << ' ';
        copy(meaning.begin(), meaning.end(), 
                ostream_iterator<string>(out, " "));
        out << '\n';
    }

    return 0;
}
