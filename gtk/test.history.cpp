#include "AiksaurusGTK_history.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	AiksaurusGTK_history hist;

	while(1)
	{
		hist.debug();
	
		cout << "Enter command: [search|back|next]: " << flush;
		string command; cin >> command;

		if (command == "search")
		{
			cout << "Enter search term: " << flush;
			string term; cin >> term;

			hist.search(term.c_str());
		}

		else if (command == "back")
		{
			hist.move_back();
		}

		else if (command == "next")
		{
			hist.move_forward();
		}
	}

	return 0;
}
