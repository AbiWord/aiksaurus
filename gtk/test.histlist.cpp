#include "AiksaurusGTK_histlist.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "Enter history list size: " << flush;
	int size; cin >> size;
	
	AiksaurusGTK_histlist foo(size);
	
	while(1)
	{
		foo.debug();

		cout << "Enter new search: " << flush;
		string s; cin >> s;
	
		foo.addItem(s.c_str());
	}

	return 0;
}

