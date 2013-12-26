#include "Arguments.h"
#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
using namespace std;

int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    string lfile, ofile;
    int maxchars, maxlinks;
    
    if (  (!A.get("--links", lfile, "")) ||
          (!A.get("--out", ofile, "")) ||
          (!A.get("--maxchars", maxchars, 17)) ||
          (!A.get("--maxlinks", maxlinks, 5))  )
    {
        cerr << "Syntax: " << argv[0] << " --links=link.# --out=w-i.# --maxchars=x --maxlinks=x" << endl;
        exit(1);
    }
    
    ifstream in(lfile.c_str());
    ofstream out(ofile.c_str());
    
    char buf[64000];

    while(in.getline(buf, 64000))
    {
        istrstream ss(buf);
        string word;
        ss >> word;

        if (word.size() > static_cast<unsigned int>(maxchars))
            continue;

        out << word;
        for(unsigned i = 0;i < ( maxchars - word.size() );++i)
        {
            out << static_cast<unsigned char>(0);
        }

        int i = 0, x;
        for(;(i < maxlinks) && (ss >> x);++i)
        {
            unsigned char ochar1 = static_cast<unsigned char>(x >> 8);
            unsigned char ochar2 = static_cast<unsigned char>(x & 0xFF);
            out << ochar1 << ochar2; 
        }

        for(;i < maxlinks;++i)
        {
            out << static_cast<unsigned char>(0xFF) 
                << static_cast<unsigned char>(0xFF);
        }
    }
    
    return 0;
}
