#include <iostream>
#include <string>
#include "Arguments.h"

using namespace std;

int main(int argc, const char** argv)
{
    Arguments A(argc, argv);

    unsigned int maxlen;
    A.get("--maxlen", maxlen, 30);

    char buf[64000];
    string x;
    
    while(cin.getline(buf, 64000))
    {
        bool nl = false;
        
        istrstream ss(buf);
        while(ss >> x)
        {
            if (x.size() <= maxlen)
            {
                cout << x << ' ';
                nl = true;
            }
        }
    
        if (nl)
            cout << endl;
    }

    return 0;
}
