#include "AiksaurusGTK_strlist.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	AiksaurusGTK_strlist foo;
	
	while(1)
	{
		foo.debug();
		
		cout << "Enter Command [pushfront or pushback or rem or remlast]: " << flush;
		string cmd; cin >> cmd;

		if (cmd == "pushfront")
		{
			cout << "String to push: " << flush;
			string x; cin >> x;
			
			foo.push_front(x.c_str());
		}

		else if (cmd == "pushback")
		{
			cout << "String to push: " << flush;
			string x; cin >> x;

			foo.push_back(x.c_str());
		}
		
		else if (cmd == "rem")
		{
			cout << "String to remove: " << flush;
			string x; cin >> x;

			foo.remove_first(x.c_str());
		}

		else if (cmd == "remlast")
		{
			foo.remove_last_element();
		}
	}

	return 0;
}
