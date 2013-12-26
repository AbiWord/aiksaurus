#include "Words.h"
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


void readRandomWordsFile(istream& in, vector<string>& words)
{
    string s;
    while(in >> s)
        words.push_back(s);
}


typedef map<string, vector<int> > LinkMap;
void readLinkedWordsFile(istream& in, LinkMap& data)
{
    static char buf[64000];
    while(in.getline(buf, 64000))
    {
        istrstream ss(buf);
        
        string name;
        vector<int> values;
        
        ss >> name;

        int x;
        while(ss >> x)
        {
            values.push_back(x);    
        } 

        data.insert( make_pair(name, values) );
    }
}



int main()
{
    cout << "Enter random words file name: " << flush;
    string randomwords; cin >> randomwords;
    
    cout << "Enter linked words file name: " << flush;
    string linkedfile; cin >> linkedfile;

    cout << "Enter meanings file name: " << flush;
    string meaningsfile; cin >> meaningsfile;
   
    cout << "Enter output file name: " << flush;
    string outputfile; cin >> outputfile;

    
    cout << "Reading in random words file..." << flush;
    vector<string> randoms;
    ifstream rin(randomwords.c_str());
    readRandomWordsFile(rin, randoms);
    cout << randoms.size() << " random words read." << endl;
    
    cout << "Reading in linked words file..." << flush;
    LinkMap links;
    ifstream lin(linkedfile.c_str());
    readLinkedWordsFile(lin, links);
    cout << links.size() << " linked words read." << endl;
    
    cout << "Reading in meanings file... " << flush;
    vector<MeaningSet> meanings;
    ifstream min(meaningsfile.c_str());
    extractMeaningFamily(min, meanings);
    cout << meanings.size() << " meaning classes read." << endl;

    cout << "Creating output file... " << endl;    
    ofstream out(outputfile.c_str());
    
    out << "<html>\n"
        << "<body bgcolor=\"#ffffff\" text=\"#000000\">\n"
        << "<h2>" << outputfile << "</h2>"
        << "<p>Meaning Sets File: " << meaningsfile << " (" << meanings.size() << ")<br>"
        << "   Linked Words File: " << linkedfile << " (" << links.size() << ")</p>\n"
        << "<table border=\"1\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">\n\n";
    
    for(unsigned int i = 0;i < randomwords.size();++i)
    {
        const string& word = randoms[i];
        LinkMap::iterator link = links.find(word);
        vector<int>& meaningsets = link->second;
        
        out << "<tr>\n"
            << "\t<th valign=\"top\" bgcolor=\"#ccffcc\" width=\"130\">" << word << "<br>"
            << meaningsets.size() << " sets</th>\n"
            << "\t<td><table border=\"1\" cellspacing=\"0\" cellpadding=\"4\" width=\"100%\">\n";
       
        for(unsigned int x = 0;x < meaningsets.size();++x)
        {
            const MeaningSet& meaning = meanings[meaningsets[x]];

            double dlr = directLinkRatio(word, meaning);
            double rlr = returnLinkRatio(word, meaning);
            double mdlr = meanDirectLinkRatio(meaning);
            double mrlr = meanReturnLinkRatio(meaning);
            
            out << "\t\t<tr bgcolor=\"#fffff0\"><td>" << x << "</td><td>";
            
            out << "<b>dlr = " << dlr << ", rlr = " << rlr 
                << " mdlr = " << mdlr << ", mrlr = " << mrlr << ", n = " 
                << meaning.size() << "</b><br>";
            
            copy(meaning.begin(), meaning.end(), ostream_iterator<string>(out, ", "));
            out << "</td></tr>\n";
        }
        
        out << "</table></td>\n";
        out << "</tr>";
    }
   
    out << "</table>\n";
    
    return 0;
}
