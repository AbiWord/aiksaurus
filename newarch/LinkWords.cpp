#include "Meanings.h"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

class WriteFile
{
    private:
        ostream& d_out;

        static vector<int> d_sizes;
        static int d_max, d_min;
        
    public:
        
        WriteFile(ostream& out) 
        : d_out(out) 
        {
        
        }
        
        void operator()(const pair<string, vector<int> >& x)
        {
            int size = x.second.size();
            
            if ((d_max < size) || (d_max == -1)) 
                d_max = size;
            
            if ((d_min > size) || (d_min == -1)) 
                d_min = size;
            
            d_sizes.push_back(size);
            
            d_out << x.first << " ";
            copy(x.second.begin(), x.second.end(), 
                    ostream_iterator<int>(d_out, " "));
            d_out << '\n';
        }

        
        void printSummary()
        {
            cout << "Generating summary statistics..." << endl;
       
            double avg = 0;
            for(unsigned int i = 0;i < d_sizes.size();++i)
            {
                avg += double(d_sizes[i]) / double(d_sizes.size());
            }
            
            sort(d_sizes.begin(), d_sizes.end());
            
            cout << "Minimum links/word: " << d_min << endl;
            cout << "Maximum links/word: " << d_max << endl;
            cout << "Average links/word: " << avg << endl;
            cout << "Median: " << d_sizes[d_sizes.size() / 2] << endl;
        }
};

int WriteFile::d_max = -1;
int WriteFile::d_min = -1;
vector<int> WriteFile::d_sizes;

int main()
{
    cout << "Enter words file name: " << flush;
    string wfile; cin >> wfile;

    cout << "Enter meanings file name: " << flush;
    string mfile; cin >> mfile;

    cout << "Enter output file name: " << flush;
    string ofile; cin >> ofile;

    cout << "Reading words file..." << endl;
    string s;
    map<string, vector<int> > words;
    ifstream win(wfile.c_str());

    while(win >> s)
       words.insert( make_pair(s, vector<int>()) ); 

    cout << "Reading meanings file..." << endl;
    ifstream min(mfile.c_str());
    MeaningFamily meanings;
    extractMeaningFamily(min, meanings);

    cout << "Linking..." << endl;
    for(unsigned int i = 0;i < meanings.size();++i) 
    {
        for(unsigned int j = 0;j < meanings[i].size();++j)
            words[ (meanings[i])[j] ].push_back(i);
    }

    cout << "Generating output..." << endl;
    ofstream out(ofile.c_str());
    WriteFile wf(out);
    for_each(words.begin(), words.end(), wf);
    wf.printSummary();
    
    return 0;
}
