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
	
		cout << "Enter command: [search|back|next|jumpbk|jumpfw]: " << flush;
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

        else if (command == "jumpbk")
        {
            cout << "Jump back how far: ";
            int jump; cin >> jump;

            AiksaurusGTK_strlist& list = const_cast<AiksaurusGTK_strlist&>(hist.list_back());
            int count = 0;
            GList* target = NULL;
            for(GList* i = const_cast<GList*>(list.list()); i != NULL; i = i->next)
            {
                count++;
                if (count == jump)
                {
                    target = i;
                    break;
                }    
            }

            if (target == NULL)
            {
                cout << "Invalid jump length." << endl;
            }

            else
            {
                hist.move_back_to(target);
            }
        }

        else if (command == "jumpfw")
        {
            cout << "Jump forward how far: ";
            int jump; cin >> jump;
            
            AiksaurusGTK_strlist& list = const_cast<AiksaurusGTK_strlist&>(hist.list_forward());
            int count = 0;
            GList* target = NULL;
            for(GList* i = const_cast<GList*>(list.list()); i != NULL; i = i->next)
            {
                count++;
                if (count == jump)
                {
                    target = i;
                    break;
                }    
            }

            if (target == NULL)
            {
                cout << "Invalid jump length." << endl;
            }
            
            else
            {
                hist.move_forward_to(target);
            }
        }
	}

	return 0;
}
