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
    int ssize; cin >> ssize;

    unsigned char* buf = 0;
    
    try
    {
        FileArray f(fname.c_str(), ssize);
    
        cout << "Structure size is " << f.getStructSize() << endl;
        cout << "File size is " << f.getFileSize() << endl;
        cout << "File contains " << f.getSize() << " structures." << endl;
    
        buf = new unsigned char[f.getStructSize()];
    
        while(1)
        {   
            cout << "Request structure: " << flush;
            int i;  cin >> i;
           
            f.read(i, buf);

            cout << "Element read successfully.  Contents: " << endl;

            for(int i = 0;i < f.getStructSize();++i)
            {
                cout << hex << buf[i] << "  ";
            }

            cout << endl;
        }
    }
    
    catch(FileArray::OpenException)
    {
        cout << "Error opening file." << endl;
    }
    
    catch(FileArray::ReadException)
    {
        cout << "Error reading file." << endl;
    }
    
    return 0;
}
