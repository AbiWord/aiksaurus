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
#include "AiksaurusGTK_picbutton.h"
#include "AiksaurusGTK_icons.h"
#include <AikSaurus.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


void AiksaurusGTK_memoryExhausted()
{
	cout << "Out of memory." << endl;
	// TO DO: handle this somehow.
}



//
// AiksaurusGTK Class 
// ------------------
//   A GTK-based interface to the AikSaurus library.
//   Eventually this should be very embeddable and nice. 
//   
class AiksaurusGTK
{
	private:
	
	// The actual thesaurus.
	
		AikSaurus *d_aiksaurus_ptr;
	

	// Copy of original word thesaurus was launched with.
	
		char* d_originalword_ptr;
		bool d_window_destroyed;
		
		
	// Pointer to a static instance.	
	
		static AiksaurusGTK* s_instance;
		static char* s_replacement;
		
		
	// Callback functions.   
	
		static gint cbExit(GtkWidget* w, GdkEventAny* e, gpointer data);
		static gint cbListClick(GtkCList* w, gint row, gint col, GdkEventButton *e, gpointer data);
		static void cbClose(GtkWidget* w, GdkEventAny* e);
		static void cbReplace(GtkWidget* w, gpointer data);
		static void cbCancel(GtkWidget* w, gpointer data);
		static void cbSearch(GtkWidget* w, gpointer data);
		static void cbForward(GtkWidget* w, gpointer data);
		static void cbBack(GtkWidget* w, gpointer data);

		static void cbSearchKeyPressed(GtkWidget* w, GdkEventKey* k, gpointer data); 
		static void cbReplaceKeyPressed(GtkWidget* w, GdkEventKey* k, gpointer data); 
		
		static void cbSelectChanged(GtkWidget* w, gpointer data);
		
		
	// GUI Widgets.
		
		// Tooltips for the dialog.
		GtkTooltips *d_tooltips_ptr;
		
		// The main window and its associated widgets
		GtkWidget* d_window_ptr;	
		GtkWidget* d_layout_ptr;	
		  
		// Word list widgets
		GtkWidget* d_wordlist_ptr;	
		  GtkWidget* d_wordlist_box_ptr;
		  GtkWidget* d_wordlist_scroller_ptr;
		  GtkWidget* d_wordlist_label_box_ptr;
		  GtkWidget* d_wordlist_label_ptr;
		  char* d_wordlist_label_text_ptr;
		  
		// The main toolbar and its associated widgets
		GtkWidget* d_toolbar_ptr;
		
		  GtkWidget* d_backbutton_box_ptr;
		  AiksaurusGTK_picbutton* d_backbutton_ptr;
		  AiksaurusGTK_picbutton* d_forwardbutton_ptr;
		  AiksaurusGTK_picbutton* d_searchbutton_ptr;
		
		  GtkWidget* d_searchbar_ptr;
		  GtkWidget* d_searchbar_label_ptr;
		  AiksaurusGTK_histlist d_searchbar_words;
		  
		// The lower replacement/ok/cancel bar and associated widgets.
		GtkWidget *d_replacebar_ptr;
		  GtkWidget *d_replacebutton_holder_ptr;
		  GtkWidget *d_replacebutton_ptr;
		  GtkWidget *d_replacebutton_label_ptr;
		  GtkWidget *d_cancelbutton_ptr;
		  GtkWidget *d_cancelbutton_label_ptr;
		  GtkWidget *d_replacewith_label_ptr;
		  GtkWidget *d_replacewith_ptr;

	
		  
	// Creation and Destruction.
		
		AiksaurusGTK(const char* search = NULL);
		~AiksaurusGTK();
		
		friend const char* AiksaurusGTK_doSearch(const char* search);

	
		void setTooltip(GtkWidget* w, const char* str);
		
		
	// GUI Initialization Routines
	
		void createWindow();
		  void createWordlist();
		
		void createToolbar();
		  void createBackbutton();
		  void createForwardbutton();	
		  void createSearchbutton();
		  void createSearchbar();
		
		void createReplacebar();
		  void createReplacebutton();
		  void createCancelbutton();
		  void createReplaceentry();

	
	// Inspection Functions

		const char* getSearchText();
		void appendSearchText(const char* str);
		
		
	// Manipulation Functions
		
		void performSearch();
		void hide();	

		const char* originalWord() const
		{
			return d_originalword_ptr;
		}
		
		void updateWordlistLabel(int count);

		void listClick(GtkCList* w, int row, int col, GdkEventButton* e);
};


void AiksaurusGTK::updateWordlistLabel(int count)
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

AiksaurusGTK* AiksaurusGTK::s_instance = NULL;
char* AiksaurusGTK::s_replacement = NULL;



//
// Interface Functions
// -------------------
//   These functions form the programmatic interface to gtkAiksaur.
//   They are the only functions that external programs should call.
//   
const char* AiksaurusGTK_doSearch(const char* search)
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






///////////////////////////////////////////////////////////////////////////////
//
// Implementation of AiksaurusGTK Class
//
///////////////////////////////////////////////////////////////////////////////

AiksaurusGTK::AiksaurusGTK(const char* search = 0)
: d_searchbar_words(12)
{
	d_wordlist_label_text_ptr = NULL;
	
	d_window_destroyed = false;
	
	if (search == 0)
		d_originalword_ptr = AiksaurusGTK_strCopy("");
	else
		d_originalword_ptr = AiksaurusGTK_strCopy(search);
	
	d_aiksaurus_ptr = new AikSaurus;
	
	createWindow();
	createToolbar();
	createWordlist();
	createReplacebar();
	
	gtk_widget_show_all(d_window_ptr);

	if (d_originalword_ptr[0] != '\0')
	{
		gtk_entry_set_text(
			GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
			d_originalword_ptr
		);

		performSearch();
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



void AiksaurusGTK::createWordlist()
{
	d_wordlist_label_box_ptr = gtk_hbox_new(false, 0);
	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_wordlist_label_box_ptr,
		false,
		false,
		0
	);
	
	d_wordlist_label_ptr = gtk_label_new("Abiword Thesaurus");

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
		GTK_SIGNAL_FUNC(cbListClick),
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

const char* AiksaurusGTK::getSearchText()
{
	return gtk_entry_get_text( 
		GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry) 
	);
}


void AiksaurusGTK::performSearch()
{
	const char* str = getSearchText();

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

	updateWordlistLabel(count);
		
	gtk_clist_thaw(
		GTK_CLIST(d_wordlist_ptr)
	);
	
	cout << "  Appending text to list." << endl;
	appendSearchText(str);

	cout << "}" << endl;
}

void AiksaurusGTK::appendSearchText(const char* str)
{	
	cout << "  AiksaurusGTK::appendSearchText(" << str << ") {" << endl;

	d_searchbar_words.addItem(str);
	
	cout << "    word pushed to front of strlist. " << endl;
	
	gtk_combo_set_popdown_strings(
		GTK_COMBO(d_searchbar_ptr),
		const_cast<GList*>(d_searchbar_words.list())
	);

	cout << "    combo box popdown strings reset." << endl;
	
	cout << "  }" << endl;
}


void AiksaurusGTK::createWindow()
{
	d_tooltips_ptr = gtk_tooltips_new();
	
	d_window_ptr = gtk_window_new(GTK_WINDOW_DIALOG);
	gtk_widget_show(d_window_ptr);
	
	gtk_window_set_title(
		GTK_WINDOW(d_window_ptr), 
		"AbiWord Thesaurus"
	);

	gtk_window_set_modal(
		GTK_WINDOW(d_window_ptr),
		true
	);
	
	// this makes the program exit when the window is closed.
	gtk_signal_connect(
		GTK_OBJECT(d_window_ptr), 
		"delete_event", 
		GTK_SIGNAL_FUNC(cbExit), 
		NULL
	);

	d_layout_ptr = gtk_vbox_new(false, 4);
	
	gtk_container_add(
		GTK_CONTAINER(d_window_ptr),
		d_layout_ptr
	);
}


void AiksaurusGTK::createToolbar()
{
	d_toolbar_ptr = gtk_hbox_new(
		false, 
		0	
	);

	createBackbutton();
	createForwardbutton();
	createSearchbar();
	createSearchbutton();
	
	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr), 		
		d_toolbar_ptr,
		false,
		false,
		5
	);
}

void AiksaurusGTK::createReplacebar()
{
	d_replacebar_ptr = gtk_hbox_new(false, 4);

	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_replacebar_ptr,
		false,
		false,
		5	
	);

	createReplaceentry();
	
	d_replacebutton_holder_ptr = gtk_hbox_new(true, 4);
	gtk_box_pack_end(
		GTK_BOX(d_replacebar_ptr),
		d_replacebutton_holder_ptr,
		false,
		false,
		5
	);
	
	createReplacebutton();
	createCancelbutton();
}


void AiksaurusGTK::createReplaceentry()
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
		GTK_SIGNAL_FUNC(cbReplaceKeyPressed),
		NULL
	);
	
	gtk_box_pack_start(
		GTK_BOX(d_replacebar_ptr),
		d_replacewith_ptr,
		false,
		false,
		2
	);
}

void AiksaurusGTK::createReplacebutton()
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
		GTK_SIGNAL_FUNC(cbReplace),
		d_replacebutton_label_ptr	
	);
}

void AiksaurusGTK::createCancelbutton()
{
	d_cancelbutton_ptr = gtk_button_new();
	d_cancelbutton_label_ptr = gtk_label_new("Cancel");
	
	gtk_signal_connect(
		GTK_OBJECT(d_cancelbutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(cbCancel),
		d_cancelbutton_label_ptr	
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

void AiksaurusGTK::setTooltip(GtkWidget* widget, const char* str)
{
	gtk_tooltips_set_tip(
		d_tooltips_ptr,
		widget,
		str,
		NULL
	);
}

void AiksaurusGTK::createBackbutton()
{
	d_backbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_backNormal
	);

	d_backbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_backHover
	);

	d_backbutton_ptr->addMenu();

	
	setTooltip(
		d_backbutton_ptr->getButton(),
		"Back"
	);

	setTooltip(
		d_backbutton_ptr->getMenuButton(),
		"Back"
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_backbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(cbBack),
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


void AiksaurusGTK::createForwardbutton()
{
	d_forwardbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_forwardNormal
	);

	d_forwardbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_forwardHover
	);

	d_forwardbutton_ptr->addMenu();
	
	setTooltip(
		d_forwardbutton_ptr->getButton(), 
		"Forward"
	);

	setTooltip(
		d_forwardbutton_ptr->getMenuButton(),
		"Forward"
	);

	gtk_signal_connect(
		GTK_OBJECT(d_forwardbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(cbForward),
		NULL	
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


void AiksaurusGTK::createSearchbutton()
{
	d_searchbutton_ptr = new AiksaurusGTK_picbutton(
		d_window_ptr,
		AiksaurusGTK_icons::s_searchNormal
	);

	d_searchbutton_ptr->setHoverPicture(
		AiksaurusGTK_icons::s_searchHover
	);

	setTooltip(
		d_searchbutton_ptr->getButton(),
		"Find Synonyms"
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_searchbutton_ptr->getButton()),
		"clicked",
		GTK_SIGNAL_FUNC(cbSearch),
		NULL
	);
	
	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_searchbutton_ptr->getButton(),
		false,
		false,
		4
	);	
}


void AiksaurusGTK::createSearchbar()
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
		GTK_SIGNAL_FUNC(cbSearchKeyPressed),
		d_searchbar_label_ptr
	);
	
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


//
// Callback Function Implementation -------------------------------------------
//
// 

void 
AiksaurusGTK::cbBack(GtkWidget* w, gpointer data)
{
	cout << "Back button pressed." << endl;
}


void 
AiksaurusGTK::cbForward(GtkWidget* w, gpointer data)
{
	cout << "Forward button pressed." << endl;
}


void 
AiksaurusGTK::cbSearch(GtkWidget* w, gpointer data)
{
//	s_instance->disconnectSearchbar();
	s_instance->performSearch();
//	s_instance->connectSearchbar();
}


void
AiksaurusGTK::cbCancel(GtkWidget* w, gpointer data)
{
	s_replacement = AiksaurusGTK_strCopy(
		s_instance->originalWord()
	);
	
	gtk_main_quit();
}


void
AiksaurusGTK::cbReplace(GtkWidget* w, gpointer data)
{
	s_replacement = AiksaurusGTK_strCopy(
		gtk_entry_get_text(GTK_ENTRY(s_instance->d_replacewith_ptr))
	);
	
	gtk_main_quit();
}


gint
AiksaurusGTK::cbExit(GtkWidget* w, GdkEventAny* e, gpointer data)
{
	s_instance->d_window_destroyed = true;

	s_replacement = AiksaurusGTK_strCopy(
		s_instance->originalWord()
	);
	
	gtk_main_quit();
	
	return 0;
}



void
AiksaurusGTK::cbSearchKeyPressed(GtkWidget* w, GdkEventKey* e, gpointer data)
{
	// Here we are detecting enter-key presses and invoking a search if 
	// the enter key is pressed.
	if (GDK_Return == e->keyval)
	{
		cbSearch(w, data);
	}
	
}



void 
AiksaurusGTK::cbReplaceKeyPressed(GtkWidget* w, GdkEventKey* e, gpointer data)
{
	// Here we are detecting enter-key presses in the replace-with entry 
	// field.  If we detect an enter-key, we need to go ahead and execute
	// the replace code.
	if (GDK_Return == e->keyval)
	{
		cbReplace(w, data);		
	}
}


void 
AiksaurusGTK::cbSelectChanged(GtkWidget* w, gpointer data)
{
	cout << "AiksaurusGTK::cbSelectChanged() invoking search." << endl;
	cbSearch(w, data);
}


gint 
AiksaurusGTK::cbListClick(GtkCList* w, gint row, gint col, GdkEventButton *e, gpointer data)
{
	s_instance->listClick(w, row, col, e);
	return 0;
}
		

void AiksaurusGTK::listClick(GtkCList* w, int row, int col, GdkEventButton* e)
{
	char* text;
	gtk_clist_get_text(w, row, col, &text);
	
	if (e->type == GDK_2BUTTON_PRESS)
	{
		gtk_entry_set_text(
			GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry),
			text
		);
	
		performSearch();
	}
	
	else
	{
		cout << "Single click: " << text << endl;
		gtk_entry_set_text(
			GTK_ENTRY(d_replacewith_ptr),
			text
		);
	}
	
}



