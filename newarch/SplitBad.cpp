#include "Meanings.h"
#include "FastSaurus.h"
#include "Ratios.h"
#include "SetUtils.h"
#include "Arguments.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

double MIN_RATIO;
double MIN_SAME_RATIO;
unsigned int PITHY_SIZE;

void doSplit(const MeaningSet& meaning, vector<MeaningSet>& results);


int main(int argc, const char** argv)
{
    Arguments A(argc, argv);
    A.get("--pithy-size", PITHY_SIZE, 10);
    A.get("--min-ratio", MIN_RATIO, .5);
    A.get("--same-ratio", MIN_SAME_RATIO, .7);
    
    cout << "Enter Meaning-Ratio File (e.g. m-r.#): " << flush;
    string file; cin >> file;
  
    cout << "Enter output file: (e.g. m.#): " << flush;
    string outfile; cin >> outfile;
    
    ifstream fin(file.c_str());
    vector<double> dlrs;
    vector<double> rlrs;
    vector<MeaningSet> meanings;
    extractMeaningFamily(fin, meanings, dlrs, rlrs);

    ofstream fout(outfile.c_str());
   
    unsigned int splitcount = 0;
    unsigned int ignorecount = 0;
    for(unsigned int i = 0;i < meanings.size();++i)
    {
        if ((i % 1000) == 0)
            cout << '.';
        
        if (dlrs[i] < MIN_RATIO)
        {
            splitcount++;
            
            vector<MeaningSet> results;
            doSplit(meanings[i], results);
           
            for(unsigned int i = 0;i < results.size();++i)
            {
                if (results[i].empty())
                   continue;
                
                copy(results[i].begin(), results[i].end(), 
                        ostream_iterator<string>(fout, " "));
                fout << "\n";
            }
        }

        else
        {
            ignorecount++;
            
            copy(meanings[i].begin(), meanings[i].end(), 
                    ostream_iterator<string>(fout, " "));
            fout << "\n";
        }
    }

    cout << "Split: " << splitcount << endl;
    cout << "Ignored: " << ignorecount << endl;
    
    return 0;
}


void doSplit(const MeaningSet& meaning, vector<MeaningSet>& results)
{
    results.push_back(MeaningSet());
    results.back().push_back(meaning[0]);
    
    for(unsigned int x = 1; x != meaning.size(); ++x)
    {
        vector<double> ratios(results.size());
        int best = 0;
        
        for(unsigned int i = 0;i < results.size();++i)
        {
            ratios[i] = directLinkRatio(meaning[x], results[i]) 
                            * results[i].size();
            
            if (ratios[i] > ratios[best])
                best = i;
        }    
         
        if (ratios[best] > MIN_SAME_RATIO * results[best].size())
        {
            results[best].push_back(meaning[x]); 
        }
        
        else
        {
            results.push_back(MeaningSet());
            results.back().push_back(meaning[x]);
        }
    }

    for(unsigned int i = 0;i < results.size();++i)
    {
        if (results[i].size() < PITHY_SIZE)
            results[i].clear();
    }
}

