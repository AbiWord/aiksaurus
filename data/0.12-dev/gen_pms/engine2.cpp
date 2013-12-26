#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include "fast.h"
#include "cleanup.h"
#include <ctime>
#include <strstream>


void run(istream& fin, ostream& fout, int count)
{
    vector< vector<string> > meanings;
    meanings.reserve(count+1);

    char buf[64000];
    int index = 0;

    while(fin.getline(buf, 64000))
    {
        if (buf[0] == '#')
            continue;

        istrstream ss(buf);
        string str;
        meanings.push_back( vector<string>() );
        while(ss >> str)        
        {  
            meanings[index].push_back(str);
        }   
        
        index++;

        if (index == count)
            break;
    }
    
    vector< vector<string> > output;
    cleanup(meanings, output);
    
    for(int i = 0;i < output.size();++i)
    {
        if (output[i].empty())
            continue;

        copy(output[i].begin(), output[i].end(),
                ostream_iterator<string>(fout, " "));
        fout << '\n';
    }
}


int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [block-size]" << endl;
        exit(0);
    }

    strstream foo;
    foo << argv[1];
    int blocksize;
    foo >> blocksize;
    
    cout << "Using blocksize " << blocksize << endl;
    
    string basename = "processed.";
    
    for(int i = 0;!cin.eof();++i)
    {
        strstream ss;
        ss << basename;
        ss << i;
        string file;
        ss >> file;
        ofstream fout(file.c_str());
        run(cin, fout, blocksize);
    }
    
    return 0;
}

