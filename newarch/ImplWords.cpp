#include <iostream>
#include <string>
#include <strstream>
#include <fstream>
using namespace std;

int main()
{
    cout << "Enter links file (link.#): " << flush;
    string lfile; cin >> lfile;

    cout << "Enter max characters per word: " << flush;
    int maxchars; cin >> maxchars;

    cout << "Enter max links per word: " << flush;
    int maxlinks; cin >> maxlinks;

    cout << "Enter output file name (w-i.#): " << flush;
    string ofile; cin >> ofile;
    
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

        while(word.size() < maxchars)
            word += ' ';
        
        out << word;

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
