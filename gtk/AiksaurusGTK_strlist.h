#ifndef INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H
#define INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H

#include <glib.h>

//
// AiksaurusGTK_strlist class
// --------------------------
//   This is a wrapper for the GList class which provides string copying
//   features so that you can add strings and store them directly in the list
//   with a minimum of fuss.
//
//   In other words, when you push_back() or push_front() strings to this list,
//   a copy of the string will be put in the list.  This makes it much easier 
//   to reuse pointers and so forth, and you don't have to remember to delete 
//   the strings you've added because the destructor does it for you.
//   

class AiksaurusGTK_strlist
{
	private:
	
		// d_list_ptr: pointer to the actual list itself.
		GList* d_list_ptr;

		// d_size: stores number of elements in list.
		int d_size;
		
		GList* find_first(const char* str);

		// do not allow copying.
		AiksaurusGTK_strlist(const AiksaurusGTK_strlist& rhs);
		const AiksaurusGTK_strlist& operator=(const AiksaurusGTK_strlist& rhs);
		
	public:

		AiksaurusGTK_strlist();
		~AiksaurusGTK_strlist();
		
		// push_back: adds str to end of list.
		void push_back(const char* str);
		
		// push_front: adds str to front of list.
		void push_front(const char* str);

		// remove_first: removes first instance of str in list if found.
		void remove_first(const char* str);
	
		// remove_last_element: removes last element of list if possible.
		void remove_last_element();
		
		// size: returns number of elements in list.
		unsigned int size() const;
		
		// getList: returns ptr to actual glist.
		const GList* list() const;

		#ifndef NDEBUG
		// debug: prints debug information.
		void debug();
		#endif
};

#endif // INCLUDED_JARED_GPL_AIKSAURUSGTK_STRLIST_H
