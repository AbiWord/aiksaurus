/*
 * AiksaurusGTK - A GTK interface to the AikSaurus library
 * Copyright (C) 2001 by Jared Davis
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include "AiksaurusGTK.h"
#include "AiksaurusGTK_utils.h"
#include "AiksaurusGTK_histlist.h"
#include "AiksaurusGTK_history.h"
#include "AiksaurusGTK_picbutton.h"
#include "AiksaurusGTK_icons.h"
#include <AikSaurus.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


static
const char* AiksaurusGTK_title = "AikSaurus";



void AiksaurusGTK_memoryExhausted()
{
	cout << "Out of memory." << endl;
	// TO DO: handle this somehow.
}



//////////////////////////////////////////////////////////////////////////
//
//   AiksaurusGTK Class
//
//////////////////////////////////////////////////////////////////////////

class AiksaurusGTK
{
	private:

		friend void AiksaurusGTK_setTitle(const char* str);
		friend const char* AiksaurusGTK_doSearch(const char* search);

		AiksaurusGTK(const char* search = NULL);
		~AiksaurusGTK();

		static char* s_replacement;
		static char* s_title;
		static AiksaurusGTK* s_instance;

		AikSaurus *d_aiksaurus_ptr;
		char* d_originalword_ptr;
		bool d_window_destroyed;


	// Dialog GUI Functions and Data Members

		GtkTooltips *d_tooltips_ptr;
		GtkWidget* d_window_ptr;
		GtkWidget* d_layout_ptr;

		void dialogCreate();
		void dialogSetTooltip(GtkWidget* w, const char* str);
		const char* dialogOriginalWord() const;

		static gint dialogExitCallback(GtkWidget* w, GdkEventAny* e, gpointer data);
		static void dialogCloseCallback(GtkWidget* w, GdkEventAny* e);

		void dialogPerformSearch();



	// Wordlist GUI Functions and Data Members

		GtkWidget* d_wordlist_ptr;
		GtkWidget* d_wordlist_box_ptr;
		GtkWidget* d_wordlist_scroller_ptr;
		GtkWidget* d_wordlist_label_box_ptr;
		GtkWidget* d_wordlist_label_ptr;
		char* d_wordlist_label_text_ptr;

		void wordlistCreate();
		void wordlistLabelUpdate(int count);
		void wordlistClick(GtkCList* w, int row, int col, GdkEventButton* e);
		static gint wordlistClickCallback(GtkCList* w, gint row, gint col, GdkEventButton *e, gpointer data);
        

	// Toolbar GUI Functions and Data Members

		GtkWidget* d_toolbar_ptr;
		GtkWidget* d_backbutton_box_ptr;

		AiksaurusGTK_history d_history;
		AiksaurusGTK_picbutton* d_backbutton_ptr;
		AiksaurusGTK_picbutton* d_forwardbutton_ptr;
		AiksaurusGTK_picbutton* d_searchbutton_ptr;

		AiksaurusGTK_histlist d_searchbar_words;
		GtkWidget* d_searchbar_ptr;
		GtkWidget* d_searchbar_label_ptr;

        bool d_ishistorymove;
        
		void toolbarCreate();
		void toolbarBackButtonCreate();
		void toolbarForwardButtonCreate();
		void toolbarSearchButtonCreate();
		void toolbarSearchBarCreate();

		void toolbarBackButtonClick();
		void toolbarForwardButtonClick();
        void toolbarBackButtonMenuClick(const char* s);
        void toolbarForwardButtonMenuClick(const char* s);

        
		void toolbarSearchBarConnect();
		void toolbarSearchBarDisconnect();
		void toolbarSearchBarAppendItem(const char* str);
		const char* toolbarSearchBarGetText();

		void toolbarUpdateNavigation();

		static void toolbarBackButtonClickCallback(GtkWidget* w, gpointer data);
		static void toolbarForwardButtonClickCallback(GtkWidget* w, gpointer data);
		static void toolbarSearchButtonClickCallback(GtkWidget* w, gpointer data);
		static void toolbarSearchBarKeyPressedCallback(GtkWidget* w, GdkEventKey* k, gpointer data);
		static void toolbarSearchBarDropdownChangedCallback(GtkList* l, GtkWidget* w, gpointer data);
        static void toolbarBackButtonMenuClickCallback(const char* s, gpointer data);
        static void toolbarForwardButtonMenuClickCallback(const char* s, gpointer data);

        
	// Replace-Bar GUI Functions and Data Members

		GtkWidget *d_replacebar_ptr;
		GtkWidget *d_replacebutton_holder_ptr;
		GtkWidget *d_replacebutton_ptr;
		GtkWidget *d_replacebutton_label_ptr;
		GtkWidget *d_cancelbutton_ptr;
		GtkWidget *d_cancelbutton_label_ptr;
		GtkWidget *d_replacewith_label_ptr;
		GtkWidget *d_replacewith_ptr;

		void replacebarCreate();
		void replacebarReplaceButtonCreate();
		void replacebarCancelButtonCreate();
		void replacebarReplaceEntryCreate();

		static void replacebarCancelButtonClickCallback(GtkWidget* w, gpointer data);
		static void replacebarReplaceButtonClickCallback(GtkWidget* w, gpointer data);
		static void replacebarReplaceEntryKeyPressedCallback(GtkWidget* w, GdkEventKey* k, gpointer data);

};


char* AiksaurusGTK::s_title = NULL;
char* AiksaurusGTK::s_replacement = NULL;
AiksaurusGTK* AiksaurusGTK::s_instance = NULL;



//////////////////////////////////////////////////////////////////////////
//
//   AiksaurusGTK Interface Functions
//
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK_setTitle(const char* str)
{
	if (str == NULL)
		return;

	if (AiksaurusGTK::s_title != NULL)
		delete[] AiksaurusGTK::s_title;

	AiksaurusGTK::s_title = AiksaurusGTK_strCopy(str);
}


const char*
AiksaurusGTK_doSearch(const char* search)
{
	if (AiksaurusGTK::s_replacement != NULL)
	{
		delete[] AiksaurusGTK::s_replacement;
	}

	AiksaurusGTK::s_instance = new AiksaurusGTK(search);

	cout << "Activating Thesaurus." << endl;
	gtk_main();
	cout << "ActivateThesaurus has control once again." << endl;

	delete AiksaurusGTK::s_instance;
	AiksaurusGTK::s_instance = NULL;

	cout << "Thesaurus destroyed." << endl;

	return AiksaurusGTK::s_replacement;
}









//////////////////////////////////////////////////////////////////////////
//
//   Creation and Destruction
//
//////////////////////////////////////////////////////////////////////////

AiksaurusGTK::AiksaurusGTK(const char* search = 0)
: d_searchbar_words(12)
{
    d_ishistorymove = false;
    
	if (s_title == NULL)
		AiksaurusGTK_setTitle(AiksaurusGTK_title);

	d_wordlist_label_text_ptr = NULL;

	d_window_destroyed = false;

	if (search == 0)
		d_originalword_ptr = AiksaurusGTK_strCopy("");
	else
		d_originalword_ptr = AiksaurusGTK_strCopy(search);

	d_aiksaurus_ptr = new AikSaurus;

	dialogCreate();
	toolbarCreate();
	wordlistCreate();
	replacebarCreate();

	gtk_widget_show_all(d_window_ptr);

	if (d_originalword_ptr[0] != '\0')
	{
		gtk_entry_set_text(
			GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
			d_originalword_ptr
		);

		dialogPerformSearch();
	}
}


AiksaurusGTK::~AiksaurusGTK()
{
	delete[] d_originalword_ptr;
	delete d_aiksaurus_ptr;

	if (!d_window_destroyed)
		gtk_widget_destroy(d_window_ptr);

	if (d_wordlist_label_text_ptr)
		delete[] d_wordlist_label_text_ptr;
}



//////////////////////////////////////////////////////////////////////////
//
//   Dialog Functions
//
//////////////////////////////////////////////////////////////////////////

const char*
AiksaurusGTK::dialogOriginalWord() const
{
	return d_originalword_ptr;
}

void
AiksaurusGTK::dialogSetTooltip(GtkWidget* widget, const char* str)
{
	gtk_tooltips_set_tip(
		d_tooltips_ptr,
		widget,
		str,
		NULL
	);
}

void AiksaurusGTK::dialogCreate()
{
	d_tooltips_ptr = gtk_tooltips_new();

	d_window_ptr = gtk_window_new(GTK_WINDOW_DIALOG);
	gtk_widget_show(d_window_ptr);

	gtk_window_set_title(
		GTK_WINDOW(d_window_ptr),
		s_title
	);

	gtk_window_set_modal(
		GTK_WINDOW(d_window_ptr),
		true
	);

	// this makes the program exit when the window is closed.
	gtk_signal_connect(
		GTK_OBJECT(d_window_ptr),
		"delete_event",
		GTK_SIGNAL_FUNC(dialogExitCallback),
	    this	
	);

	d_layout_ptr = gtk_vbox_new(false, 4);

	gtk_container_add(
		GTK_CONTAINER(d_window_ptr),
		d_layout_ptr
	);
}

gint
AiksaurusGTK::dialogExitCallback(GtkWidget* w, GdkEventAny* e, gpointer data)
{
	s_instance->d_window_destroyed = true;

	s_replacement = AiksaurusGTK_strCopy(
		s_instance->dialogOriginalWord()
	);

	gtk_main_quit();

	return 0;
}

void AiksaurusGTK::dialogPerformSearch()
{
	const char* str = toolbarSearchBarGetText();

	// don't re-do the search if it is the current search.
	if (AiksaurusGTK_strEquals(d_aiksaurus_ptr->word(), str))
	{
		return;
	}


	gtk_clist_freeze(
		GTK_CLIST(d_wordlist_ptr)
	);

	gtk_clist_clear(
		GTK_CLIST(d_wordlist_ptr)
	);

	int count;
	if (d_aiksaurus_ptr->find(str))
	{
		count = d_aiksaurus_ptr->count();
		char pos;

		for(const char* r = d_aiksaurus_ptr->next(pos);r[0] != '\0';r = d_aiksaurus_ptr->next(pos))
		{
			gtk_clist_append(
				GTK_CLIST(d_wordlist_ptr),
				const_cast<gchar**>(&r)
			);

		}
	}

	else
	{
		count = 0;
		for(const char* r = d_aiksaurus_ptr->similar(); r[0] != '\0';r = d_aiksaurus_ptr->similar())
		{
			gtk_clist_append(
				GTK_CLIST(d_wordlist_ptr),
				const_cast<gchar**>(&r)
			);
		}
	}

    if (!d_ishistorymove)
    {
        d_history.search(str);
        d_history.debug();
    }
    
    toolbarUpdateNavigation();
	
    wordlistLabelUpdate(count);

	gtk_clist_thaw(
		GTK_CLIST(d_wordlist_ptr)
	);

	toolbarSearchBarAppendItem(str);
}



//////////////////////////////////////////////////////////////////////////
//
//   Words List Functions
//
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK::wordlistCreate()
{
	d_wordlist_label_box_ptr = gtk_hbox_new(false, 0);
	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_wordlist_label_box_ptr,
		false,
		false,
		0
	);

	d_wordlist_label_ptr = gtk_label_new(s_title);

	gtk_label_set_justify(
		GTK_LABEL(d_wordlist_label_ptr),
		GTK_JUSTIFY_LEFT
	);

	gtk_box_pack_start(
		GTK_BOX(d_wordlist_label_box_ptr),
		d_wordlist_label_ptr,
		false,
		false,
		4
	);

	d_wordlist_scroller_ptr = gtk_scrolled_window_new(
		NULL,
		NULL
	);

	gtk_scrolled_window_set_policy(
		GTK_SCROLLED_WINDOW(d_wordlist_scroller_ptr),
		GTK_POLICY_NEVER,
		GTK_POLICY_AUTOMATIC
	);

	d_wordlist_ptr = gtk_clist_new(1);
	gtk_widget_set_usize(
		d_wordlist_ptr,
		350,
		300
	);

	gtk_signal_connect(
		GTK_OBJECT(d_wordlist_ptr),
		"select-row",
		GTK_SIGNAL_FUNC(wordlistClickCallback),
		this
	);

	gtk_container_add(
		GTK_CONTAINER(d_wordlist_scroller_ptr),
		d_wordlist_ptr
	);

	d_wordlist_box_ptr = gtk_hbox_new(false, 10);

	gtk_box_pack_start(
		GTK_BOX(d_wordlist_box_ptr),
		d_wordlist_scroller_ptr,
		true,
		true,
		10
	);

	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_wordlist_box_ptr,
		true,
		true,
		0
	);
}


void
AiksaurusGTK::wordlistLabelUpdate(int count)
{
	static const char* nosyns_1 = "No synonyms found for ";
	static const char* nosyns_2 = ".  Nearby words are:";
	static const char* xfound = " synonyms found for ";
	static const char* colon = ":";

	if (d_wordlist_label_text_ptr)
	{
		delete[] d_wordlist_label_text_ptr;
		d_wordlist_label_text_ptr = NULL;
	}

	if (count == 0)
	{
		char* s1 = AiksaurusGTK_strConcat(nosyns_1, d_aiksaurus_ptr->word());
		if (!s1) AiksaurusGTK_memoryExhausted();

		d_wordlist_label_text_ptr = AiksaurusGTK_strConcat(s1, nosyns_2);
		delete[] s1;
	}

	else
	{
		char* s1 = AiksaurusGTK_intToString(count);
		if (!s1) AiksaurusGTK_memoryExhausted();

		char* s2 = AiksaurusGTK_strConcat(s1, xfound);
		if (!s2) AiksaurusGTK_memoryExhausted();
		delete[] s1;

		char* s3 = AiksaurusGTK_strConcat(s2, d_aiksaurus_ptr->word());
		if (!s3) AiksaurusGTK_memoryExhausted();
		delete[] s2;

		d_wordlist_label_text_ptr = AiksaurusGTK_strConcat(s3, colon);
		delete[] s3;
    }

	if (!d_wordlist_label_ptr)
		AiksaurusGTK_memoryExhausted();

	gtk_label_set_text(
		GTK_LABEL(d_wordlist_label_ptr),
		d_wordlist_label_text_ptr
	);
}


void
AiksaurusGTK::wordlistClick(GtkCList* w, int row, int col, GdkEventButton* e)
{
    toolbarSearchBarDisconnect();

	char* text;
	gtk_clist_get_text(w, row, col, &text);

	if (e->type == GDK_2BUTTON_PRESS)
	{
		gtk_entry_set_text(
			GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
			text
		);

		dialogPerformSearch();
	}

	else
	{
		gtk_entry_set_text(
			GTK_ENTRY(d_replacewith_ptr),
			text
		);
	}

    toolbarSearchBarConnect();
}


gint
AiksaurusGTK::wordlistClickCallback(GtkCList* w, gint row, gint col, GdkEventButton *e, gpointer data)
{
	s_instance->wordlistClick(w, row, col, e);
	return 0;
}



//////////////////////////////////////////////////////////////////////////
//
//   Tool Bar Functions
//
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK::toolbarCreate()
{
	d_toolbar_ptr = gtk_hbox_new(
		false,
		0
	);

	toolbarBackButtonCreate();
	toolbarForwardButtonCreate();
	toolbarSearchBarCreate();
	toolbarSearchButtonCreate();

	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_toolbar_ptr,
		false,
		false,
		5
	);

    toolbarUpdateNavigation();
}


void
AiksaurusGTK::toolbarBackButtonCreate()
{
	d_backbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_backNormal
	);

	d_backbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_backHover
	);

	d_backbutton_ptr->addMenu(
        d_history.list_back(),
        GTK_SIGNAL_FUNC(toolbarBackButtonMenuClickCallback),
        this        
    );

	dialogSetTooltip(
		d_backbutton_ptr->getMenuButton(),
		"Back"
	);

	gtk_signal_connect(
		GTK_OBJECT(d_backbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(toolbarBackButtonClickCallback),
		this
	);

	d_backbutton_box_ptr = gtk_hbox_new(false, 0);

	gtk_box_pack_start(
		GTK_BOX(d_backbutton_box_ptr),
		d_backbutton_ptr->getButton(),
		false,
		false,
	 	0
	);

	gtk_box_pack_start(
		GTK_BOX(d_backbutton_box_ptr),
		d_backbutton_ptr->getMenuButton(),
		false,
		false,
		0
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_backbutton_box_ptr,
		false,
		false,
		4
	);
}


void
AiksaurusGTK::toolbarForwardButtonCreate()
{
	d_forwardbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_forwardNormal
	);

	d_forwardbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_forwardHover
	);

	d_forwardbutton_ptr->addMenu(
        d_history.list_forward(),
        GTK_SIGNAL_FUNC(toolbarForwardButtonMenuClickCallback),
        this
    );

	dialogSetTooltip(
		d_forwardbutton_ptr->getMenuButton(),
		"Forward"
	);

	gtk_signal_connect(
		GTK_OBJECT(d_forwardbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(toolbarForwardButtonClickCallback),
	    this	
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_forwardbutton_ptr->getButton(),
		false,
		false,
		0
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_forwardbutton_ptr->getMenuButton(),
		false,
		false,
		0
	);
}


void
AiksaurusGTK::toolbarSearchButtonCreate()
{
	d_searchbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_searchNormal
	);

	d_searchbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_searchHover
	);

	dialogSetTooltip(
		d_searchbutton_ptr->getButton(),
		"Find Synonyms"
	);

	gtk_signal_connect(
		GTK_OBJECT(d_searchbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(toolbarSearchButtonClickCallback),
	    this	
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_searchbutton_ptr->getButton(),
		false,
		false,
		4
	);
}


void AiksaurusGTK::toolbarSearchBarCreate()
{
	d_searchbar_label_ptr = gtk_label_new("  Look up:");
	d_searchbar_ptr = gtk_combo_new();

	gtk_combo_set_use_arrows(
		GTK_COMBO(d_searchbar_ptr),
		false
	);

	gtk_combo_disable_activate(
		GTK_COMBO(d_searchbar_ptr)
	);

	gtk_signal_connect(
		GTK_OBJECT(
			GTK_COMBO(d_searchbar_ptr)->entry
		),
		"key-press-event",
		GTK_SIGNAL_FUNC(toolbarSearchBarKeyPressedCallback),
	    this	
	);

	toolbarSearchBarConnect();

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_searchbar_label_ptr,
		false,
		false,
		5
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_searchbar_ptr,
		true,
		true,
		5
	);
}


void AiksaurusGTK::toolbarSearchBarAppendItem(const char* str)
{
	d_searchbar_words.addItem(str);

	gtk_combo_set_popdown_strings(
		GTK_COMBO(d_searchbar_ptr),
		const_cast<GList*>(d_searchbar_words.list())
	);
}


void
AiksaurusGTK::toolbarUpdateNavigation()
{
    if (d_history.size_back())
        d_backbutton_ptr->enable();
    else
        d_backbutton_ptr->disable();

    dialogSetTooltip(
        d_backbutton_ptr->getButton(),
        d_history.tip_back()
    );

    if (d_history.size_forward())
        d_forwardbutton_ptr->enable();
    else
        d_forwardbutton_ptr->disable();

    dialogSetTooltip(
        d_forwardbutton_ptr->getButton(),
        d_history.tip_forward()
    );

    d_backbutton_ptr->updateMenuOptions();
    d_forwardbutton_ptr->updateMenuOptions();
}


void
AiksaurusGTK::toolbarSearchBarConnect()
{
    cout << "Searchbar Connected" << endl;
    gtk_signal_connect(
        GTK_OBJECT(GTK_COMBO(d_searchbar_ptr)->list),
        "select-child",
        GTK_SIGNAL_FUNC(toolbarSearchBarDropdownChangedCallback),
        this
    );
}


void
AiksaurusGTK::toolbarSearchBarDisconnect()
{
    cout << "Disconnected" << endl;
    gtk_signal_disconnect_by_func(
            GTK_OBJECT(GTK_COMBO(d_searchbar_ptr)->list),
            GTK_SIGNAL_FUNC(toolbarSearchBarDropdownChangedCallback),
            this
    );
}


const char*
AiksaurusGTK::toolbarSearchBarGetText()
{
	return gtk_entry_get_text(
		GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry)
	);
}


void
AiksaurusGTK::toolbarBackButtonClick()
{
    assert(d_history.size_back());
    d_history.debug();
    d_history.move_back();
    d_history.debug();

    gtk_entry_set_text(
            GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
            d_history.current()
    );

    d_ishistorymove = true;
    dialogPerformSearch();
    d_ishistorymove = false;
}

void
AiksaurusGTK::toolbarForwardButtonClick()
{
    cout << "toolbarForwardButtonClick() function: " << endl;
    assert(d_history.size_forward());

    d_history.move_forward();
    d_history.debug();

    gtk_entry_set_text(
			GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
			d_history.current()
	);

    d_ishistorymove = true;
    dialogPerformSearch();
    d_ishistorymove = false;
}

void 
AiksaurusGTK::toolbarBackButtonMenuClick(const char* s)
{
    cout << "  <- Move Back to " << s << endl;
}

void 
AiksaurusGTK::toolbarForwardButtonMenuClick(const char* s)
{
    cout << "  -> Move Forward to " << s << endl;
}

void
AiksaurusGTK::toolbarSearchButtonClickCallback(GtkWidget* w, gpointer data)
{
	s_instance->toolbarSearchBarDisconnect();
	s_instance->dialogPerformSearch();
	s_instance->toolbarSearchBarConnect();
}

void
AiksaurusGTK::toolbarBackButtonClickCallback(GtkWidget* w, gpointer data)
{
    static_cast<AiksaurusGTK*>(data)->toolbarBackButtonClick();
}

void
AiksaurusGTK::toolbarForwardButtonClickCallback(GtkWidget* w, gpointer data)
{
    static_cast<AiksaurusGTK*>(data)->toolbarForwardButtonClick();
}
        
void 
AiksaurusGTK::toolbarBackButtonMenuClickCallback(const char* s, gpointer data)
{
    static_cast<AiksaurusGTK*>(data)->toolbarBackButtonMenuClick(s);
}

void 
AiksaurusGTK::toolbarForwardButtonMenuClickCallback(const char* s, gpointer data)
{
    static_cast<AiksaurusGTK*>(data)->toolbarForwardButtonMenuClick(s);
}

void
AiksaurusGTK::toolbarSearchBarKeyPressedCallback(GtkWidget* w, GdkEventKey* e, gpointer data)
{
	// Here we are detecting enter-key presses and invoking a search if
	// the enter key is pressed.
	if (GDK_Return == e->keyval)
	{
		toolbarSearchButtonClickCallback(w, data);
	}

}

void
AiksaurusGTK::toolbarSearchBarDropdownChangedCallback(GtkList* l, GtkWidget* w, gpointer data)
{
	cout << "SELECT CHILD CALLBACK!!" << endl;
//	toolbarSearchButtonClickCallback(w, data);
}



//////////////////////////////////////////////////////////////////////////
//
//   Replace Bar Functions
//
//////////////////////////////////////////////////////////////////////////

void
AiksaurusGTK::replacebarCreate()
{
	d_replacebar_ptr = gtk_hbox_new(false, 4);

	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_replacebar_ptr,
		false,
		false,
		5
	);

	replacebarReplaceEntryCreate();

	d_replacebutton_holder_ptr = gtk_hbox_new(true, 4);
	gtk_box_pack_end(
		GTK_BOX(d_replacebar_ptr),
		d_replacebutton_holder_ptr,
		false,
		false,
		5
	);

	replacebarReplaceButtonCreate();
	replacebarCancelButtonCreate();
}


void
AiksaurusGTK::replacebarReplaceEntryCreate()
{
	d_replacewith_label_ptr = gtk_label_new("  Replace With:");

	gtk_box_pack_start(
		GTK_BOX(d_replacebar_ptr),
		d_replacewith_label_ptr,
		false,
		false,
		0
	);

	d_replacewith_ptr = gtk_entry_new();

	gtk_signal_connect(
		GTK_OBJECT(d_replacewith_ptr),
		"key-press-event",
		GTK_SIGNAL_FUNC(replacebarReplaceEntryKeyPressedCallback),
	    this	
	);

	gtk_box_pack_start(
		GTK_BOX(d_replacebar_ptr),
		d_replacewith_ptr,
		false,
		false,
		2
	);
}


void
AiksaurusGTK::replacebarReplaceButtonCreate()
{
	d_replacebutton_ptr = gtk_button_new();
	d_replacebutton_label_ptr = gtk_label_new("  Replace  ");

	gtk_container_add(
		GTK_CONTAINER(d_replacebutton_ptr),
		d_replacebutton_label_ptr
	);

	gtk_box_pack_start(
		GTK_BOX(d_replacebutton_holder_ptr),
		d_replacebutton_ptr,
		true,
		true,
		0
	);

	gtk_signal_connect(
		GTK_OBJECT(d_replacebutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(replacebarReplaceButtonClickCallback),
	    this	
	);
}


void
AiksaurusGTK::replacebarCancelButtonCreate()
{
	d_cancelbutton_ptr = gtk_button_new();
	d_cancelbutton_label_ptr = gtk_label_new("Cancel");

	gtk_signal_connect(
		GTK_OBJECT(d_cancelbutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(replacebarCancelButtonClickCallback),
	    this	
	);

	gtk_container_add(
		GTK_CONTAINER(d_cancelbutton_ptr),
		d_cancelbutton_label_ptr
	);

	gtk_box_pack_start(
		GTK_BOX(d_replacebutton_holder_ptr),
		d_cancelbutton_ptr,
		true,
		true,
		0
	);
}


void
AiksaurusGTK::replacebarCancelButtonClickCallback(GtkWidget* w, gpointer data)
{
	s_replacement = AiksaurusGTK_strCopy(
		s_instance->dialogOriginalWord()
	);

	gtk_main_quit();
}


void
AiksaurusGTK::replacebarReplaceButtonClickCallback(GtkWidget* w, gpointer data)
{
	s_replacement = AiksaurusGTK_strCopy(
		gtk_entry_get_text(GTK_ENTRY(s_instance->d_replacewith_ptr))
	);

	gtk_main_quit();
}

void
AiksaurusGTK::replacebarReplaceEntryKeyPressedCallback(GtkWidget* w, GdkEventKey* e, gpointer data)
{
	// Here we are detecting enter-key presses in the replace-with entry
	// field.  If we detect an enter-key, we need to go ahead and execute
	// the replace code.
	if (GDK_Return == e->keyval)
	{
		replacebarReplaceButtonClickCallback(w, data);
	}
}

