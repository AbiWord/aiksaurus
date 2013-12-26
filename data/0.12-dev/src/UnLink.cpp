#include "Meanings.h"
#include "FastSaurus.h"
#include "Ratios.h"
#include <strstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


typedef map<string, vector<int> > LinkMap;

unsigned int MAX_SIZE;
LinkMap links;
MeaningFamily meanings;

void MakeMeanings(const string& file, MeaningFamily& meanings);
void MakeLinks(MeaningFamily& meanings, LinkMap& links);
void KillLinks(MeaningFamily& meanings, LinkMap& links, unsigned int max);
void WriteMeanings(const string& file, MeaningFamily& meanings);


int main()
{
    cout << "Enter meanings file name (m.#): " << flush;
    string mfile; cin >> mfile;

    cout << "Enter maximum links size: " << flush;
    cin >> MAX_SIZE;
    
    cout << "Output meaning file (m.#): " << flush;
    string outfile; cin >> outfile;
    
    MakeMeanings(mfile, meanings);
    MakeLinks(meanings, links);    
    KillLinks(meanings, links, MAX_SIZE); 
    WriteMeanings(outfile, meanings);
    
    return 0;
}

void MakeMeanings(const string& file, MeaningFamily& meanings)
{
    cout << "Reading meanings file..." << flush;
    ifstream min(file.c_str());
    extractMeaningFamily(min, meanings);
    cout << " (" << meanings.size() << " meanings read.)" << endl;
}

void MakeLinks(MeaningFamily& meanings, LinkMap& links)
{
    cout << "Generating link map..." << flush;
    for(unsigned int i = 0;i < meanings.size();++i)
    {
        MeaningSet& ms = meanings[i];
        for(unsigned int j = 0;j < ms.size();++j)
        {
            links[ ms[j] ].push_back(i);
        }
    }
    cout << " (" << links.size() << " link structures.)" << endl;
}

void KillLinks(MeaningFamily& meanings, LinkMap& links, unsigned int max)
{
    cout << "Killing links..." << flush;
    unsigned int numKilled = 0;
    
    for(LinkMap::iterator x = links.begin(); x != links.end(); ++x)
    {
        if (x->second.size() >= max)   
        {
            // need to kill links.
            // calculate scores for each meaning set.
            vector<double> scores(x->second.size());
            for(unsigned int i = 0; i < scores.size();++i)
            {
                scores[i] = directLinkRatio(
                        x->first, meanings[x->second[i]]);
            }
            
            // pick the sets with the worst scores, and 
            // kill those links.
            for(unsigned int i = 0;i < (scores.size() - max);++i)
            {
                // find worst score.
                int worst = 0;
                for(unsigned int j = 0; j < scores.size(); ++j)
                {
                    if (scores[j] < scores[worst])
                        worst = j;
                }
            
                int bad_set = x->second[worst];
                
                // preevnt same score from being eliminated
                // several times over and over 
                scores[worst] = 2;
                
                // eliminate the link to the bad set.
                x->second[worst] = -1;    

                // eliminate the word from the bad set.
                MeaningSet& bs = meanings[bad_set];
                for(unsigned int j = 0; j < bs.size(); ++j)
                {
                    if (bs[j] == x->first)
                    {
                        bs[j] = "";
                        break;
                    }
                }
                    
                numKilled++;
            }
        }
    }
    
    cout << " (" << numKilled << " links killed.)" << endl;
}

void WriteMeanings(const string& file, MeaningFamily& meanings)
{
    cout << "Writing new meanings file..." << flush;
    ofstream out(file.c_str());

    for(MeaningFamily::iterator x = meanings.begin(); x != meanings.end(); ++x)
    {
        MeaningSet& ms = *x;

        for(unsigned int i = 0;i < ms.size();++i)
        {
            if (ms[i] != "")
                out << ms[i] << ' ';
        }

        out << endl;
    }
    
    cout << " Done. " << endl;
}

