#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
#include "andrew_vec.h"

int main()
{
    vector<string> avec;
    equivClass("fool", "apish", avec);

    copy(avec.begin(), avec.end(), ostream_iterator<string>(cout, ", "));
    
    return 0;
}
