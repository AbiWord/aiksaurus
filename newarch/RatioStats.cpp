#include "Meanings.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    cout << "Enter Meaning-Ratio File (e.g. m-r.#): " << flush;
    string file; cin >> file;

    ifstream fin(file.c_str());
    vector<double> dlrs;
    vector<double> rlrs;
    vector<MeaningSet> meanings;
    extractMeaningFamily(fin, meanings, dlrs, rlrs);

    int n = 0;

    do
    {
        double avg_dlr = 0;
        double min_dlr = 2;
        double max_dlr = -1;
  
        unsigned int over_n_count = 0;
        
        vector<double> cp;
        
        for(unsigned int i = 0;i < meanings.size();++i)
        {
            if (meanings[i].size() >= static_cast<unsigned int>(n))
            {
                over_n_count++;
                cp.push_back(dlrs[i]);
            }
        }
        
        for(unsigned int i = 0;i < meanings.size();++i)
        {
            if (meanings[i].size() >= static_cast<unsigned int>(n))
            {
                avg_dlr += dlrs[i] / over_n_count;
                min_dlr = min(dlrs[i], min_dlr);
                max_dlr = max(dlrs[i], max_dlr);
            }
        }
        
        sort(cp.begin(), cp.end());

    
        cout << "sets with more than " << n << " elements: " 
             << over_n_count << endl;
    
        cout << "average link ratio: " << avg_dlr << endl;
        cout << "minimum link ratio: " << min_dlr << endl;
        cout << "maximum link ratio: " << max_dlr << endl; 
        cout << "median link raito: " << cp[cp.size() / 2] << endl;
    
        cout << "\nYou can refine results to only include sets with \n"
             << "above a certain number of results (n).\n"
             << "Input n (-1 to quit): " << flush;
        
        cin >> n;
        
    } while(n >= 0);

    while(1)
    {
        double pct;
   
        cout << "\nYou can now query to find the number of sets with \n"
             << "mdlr < pct.  For example, entering .1 would give you \n"
             << "count of all sets with less than 10\% dlr.\n"
             << "Input pct (-1 to quit): " << flush;

        cin >> pct;

        if (pct < 0)
            break;

        int result = 0;
        for(unsigned int i = 0;i < meanings.size();++i)
        {
            if (dlrs[i] < pct)
                result++;
        }
        
        cout << "Number of sets: " << result << endl;
    }
    
    return 0;
}
