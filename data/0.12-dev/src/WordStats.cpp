#include <iostream>
#include <string>
#include <strstream>
#include <vector>

using namespace std;

int main()
{
    vector<int> sizes;
    string word;
    while(cin >> word)
    {
        sizes.push_back(word.size());
    }
    
    double average = 0;
    int max = sizes[0];
    int min = sizes[0];
    
    for(unsigned int i = 0;i < sizes.size();++i)
    {
        if (sizes[i] > max)
            max = sizes[i];

        if (sizes[i] < min)
            min = sizes[i];

        average += double(sizes[i]) / sizes.size();
    }

    cout << "min: " << min << endl;
    cout << "max: " << max << endl;
    cout << "avg: " << average << endl;
    return 0;
}
