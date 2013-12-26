#include <iostream>
#include <string>
#include <strstream>
#include <vector>

int main()
{
    int killed = 0;
    
    char buf[64000];
    while(cin.getline(buf, 64000))
    {
        int size = 0;
        for(int i = 0;buf[i] != '\0';++i)
        {
            if (buf[i] == ' ')
                size++;
        }

        if (size < 500)
        {
            cout << buf << '\n';
        }
        else
        {
            ++killed;
        }
    }

    cerr << "killed: " << killed << endl;
    return 0;
}
