#include "Words.h"
#include "Ratios.h"
#include "Meanings.h"
#include "FastSaurus.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    cout << "Enter meanings file name: " << flush;
    string meaningsfile; cin >> meaningsfile;
   
    cout << "Enter output file name: " << flush;
    string outputfile; cin >> outputfile;

    
    cout << "Reading in meanings file... " << flush;
    vector<MeaningSet> meanings;
    ifstream min(meaningsfile.c_str());
    extractMeaningFamily(min, meanings);
    cout << meanings.size() << " meaning classes read." << endl;
    
    
    ofstream out(outputfile.c_str());
    
    for(vector<MeaningSet>::iterator x = meanings.begin();x != meanings.end();++x)
    { 
        MeaningSet& ms = *x;
       
        for(unsigned int i = 0;i < ms.size();++i)
        {
            double rlr = returnLinkRatio(ms[i], ms);
            double dlr = directLinkRatio(ms[i], ms);

            if (rlr + dlr >= .2)
                out << ms[i] << ' ';
        }

        out << '\n';
    }
    
    return 0;
}
