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
		
		cout << "Enter Command [pushfr|pushbk|popfr|popbk|rem]: " << flush;
		string cmd; cin >> cmd;

		if (cmd == "pushfr")
		{
			cout << "String to push: " << flush;
			string x; cin >> x;
			
			foo.push_front(x.c_str());
		}

		else if (cmd == "pushbk")
		{
			cout << "String to push: " << flush;
			string x; cin >> x;

			foo.push_back(x.c_str());
		}
		
		else if (cmd == "popfr")
		{
			foo.pop_front();
		}

		else if (cmd == "popbk")
		{
			foo.pop_back();
		}
		
		else if (cmd == "rem")
		{
			cout << "String to remove: " << flush;
			string x; cin >> x;

			foo.remove_first(x.c_str());
		}
	}

	return 0;
}
