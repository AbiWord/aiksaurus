#include "FileArray.h"
#include <string>
#include <iostream>
using namespace std;
using namespace AiksaurusImpl;

int main()
{
    cout << "Enter file name: " << flush;
    string fname; cin >> fname;

    cout << "Enter struct size: " << flush;
    long ssize; cin >> ssize;

    bool success;
    FileArray f(fname.c_str(), ssize, success);

    if (!success)
    {
        cout << "Error opening file for reading." << endl;
        return 0;
    }

    cout << "File is " << f.getBytes() << " bytes long." << endl;
    cout << "So file contains " << f.getBytes() / f.getStructSize()
         << " structures." << endl;

    unsigned char *buf = new unsigned char[f.getStructSize()];
    
    while(1)
    {   
        cout << "Request structure: " << flush;
        long i;  cin >> i;

        if (!f.at(i, buf))
        {
            cout << "Error reading element " << dec << i << endl;
        }

        else
        {
            cout << "Element read successfully.  Contents: " << endl;

            for(long i = 0;i < f.getStructSize();++i)
            {
                cout << hex << buf[i] << "  ";
            }

            cout << endl;
        }
    }   

    delete buf;
    
    return 0;
}
