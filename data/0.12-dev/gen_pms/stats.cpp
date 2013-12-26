#include <iostream>
#include <string>
#include <strstream>
#include <vector>

int main()
{
    vector<int> sizes;
    char buf[64000];
    while(cin.getline(buf, 64000))
    {
        int size = 0;
        for(int i = 0;buf[i] != '\0';++i)
        {
            if (buf[i] == ' ')
                size++;
        }
        sizes.push_back(size);
    }

    double average = 0;
    int max = sizes[0];
    int min = sizes[0];
    int over100 = 0;
    int over200 = 0;
    int over500 = 0;
    
    for(int i = 0;i < sizes.size();++i)
    {
        if (sizes[i] > max)
            max = sizes[i];

        if (sizes[i] < min)
            min = sizes[i];

        average += double(sizes[i]) / sizes.size();

        if (sizes[i] > 100)
            over100++;

        if (sizes[i] > 200)
            over200++;

        if (sizes[i] > 500)
        {
            over500++;
            cout << "over 500: " << i << endl;
        }
    }

    cout << "min: " << min << endl;
    cout << "max: " << max << endl;
    cout << "avg: " << average << endl;
    cout << "over100: " << over100 << endl;
    cout << "over200: " << over200 << endl;
    cout << "over500: " << over500 << endl;
    return 0;
}
