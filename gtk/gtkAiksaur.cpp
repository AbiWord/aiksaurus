#include <AikSaurus.h>
#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
using namespace std;


//
// GtkAiksaur Callback Functions
// -----------------------------
//   GTK uses callback functions for us to know when things have happened.
//   These callback functions are needed for the thesaurus dialog to handle
//   user input.  We can make them static to keep from polluting the global
//   namespace too much.
//

static gint 
GtkAiksaur_exitCallback(GtkWidget* w, GdkEventAny* e, gpointer data);
	
static void 
GtkAiksaur_backButtonCallback(GtkWidget* w, gpointer data);
	
static void 
GtkAiksaur_forwardButtonCallback(GtkWidget* w, gpointer data);
	
static void 
GtkAiksaur_searchButtonCallback(GtkWidget* w, gpointer data);


// 
// GtkAiksaur Class 
// ----------------
//   A GTK-based interface to the AikSaurus library.
//   Eventually this should be very embeddable and nice. 
//   
class GtkAiksaur
{
	// Callback Function Friendships
	friend gint GtkAiksaur_exitCallback(GtkWidget *w, GdkEventAny *e, gpointer data);
	friend void GtkAiksaur_backButtonCallback(GtkWidget *w, gpointer data);
	friend void GtkAiksaur_forwardButtonCallback(GtkWidget *w, gpointer data);
	friend void GtkAiksaur_searchButtonCallback(GtkWidget *w, gpointer data);
	
	// Activate Function Friendship
	friend const char* ActivateThesaurus(const char* search);
	
	private:
	
		// Static pointer to the instance.
		static GtkAiksaur* s_instance;
	
		// The main dialog window and layout component.
		GtkWidget* d_window_ptr;
		  GtkWidget* d_layout_ptr;

		// The main tool bar and it's associated widgets 
		GtkWidget* d_toolbar_ptr;
		  GtkWidget* d_backbutton_ptr;
		  GtkWidget* d_backbutton_label_ptr;
		  GtkWidget* d_forwardbutton_ptr;
		  GtkWidget* d_forwardbutton_label_ptr;
		  GtkWidget* d_searchbutton_ptr;
		  GtkWidget* d_searchbutton_label_ptr;
		  GtkWidget* d_searchbar_ptr;
		  GtkWidget* d_searchbar_label_ptr;

		// A listbox to list our synonyms.
		GtkWidget* d_wordlist_ptr;

		// The replace/ok/cancel bar and associated widgets
		GtkWidget *d_replacebar_ptr;
		  GtkWidget *d_okbutton_ptr;
		  GtkWidget *d_okbutton_label_ptr;
		  GtkWidget *d_cancelbutton_ptr;
		  GtkWidget *d_cancelbutton_label_ptr;
		  GtkWidget *d_replacewith_label_ptr;
		  GtkWidget *d_replacewith_ptr;
		
		  
		// The Actual Thesaurus
		AikSaurus *d_aiksaurus_ptr;
		
		// Component creation functions, actually build the UI.
		void createWindow();
		
		void createToolbar();
		  void createBackbutton();
		  void createForwardbutton();	
		  void createSearchbutton();
		  void createSearchbar();
		
		void createReplacebar();
		  void createOkbutton();
		  void createCancelbutton();
		  void createReplaceentry();
		
		void performSearch(const char* str);
		
		const char* getSearchText();
		
		GtkAiksaur();	
};


GtkAiksaur* GtkAiksaur::s_instance = NULL;

//
// Interface Functions
// -------------------
//   These functions form the programmatic interface to gtkAiksaur.
//   They are the only functions that external programs should call.
//   
const char* ActivateThesaurus(const char* search)
{
	if (GtkAiksaur::s_instance == NULL)
	{
		GtkAiksaur::s_instance = new GtkAiksaur;
	}

	// To do: run a search for 'search'.
	
	gtk_main();

	return "Foo";
}






///////////////////////////////////////////////////////////////////////////////
//
// Implementation of GtkAiksaur Class
//
///////////////////////////////////////////////////////////////////////////////

GtkAiksaur::GtkAiksaur()
{	
	d_aiksaurus_ptr = new AikSaurus;
	
	createWindow();
	createToolbar();
	
	d_wordlist_ptr = gtk_clist_new(1);

	gtk_box_pack_start(
		GTK_BOX(d_layout_ptr),
		d_wordlist_ptr,
		true,
		true,
		5
	);
	
	createReplacebar();
	
	gtk_widget_show_all(d_window_ptr);
}


const char* GtkAiksaur::getSearchText()
{
	return gtk_entry_get_text( 
		GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry) 
	);
}


void GtkAiksaur::performSearch(const char* str)
{
	if (d_aiksaurus_ptr->find(str))
	{
		char pos;

		gtk_clist_clear(
			GTK_CLIST(d_wordlist_ptr)
		);
		
		for(const char* r = d_aiksaurus_ptr->next(pos);r[0] != '\0';r = d_aiksaurus_ptr->next(pos))
		{
			gtk_clist_append(
				GTK_CLIST(d_wordlist_ptr),
				const_cast<gchar**>(&r)
			);
			
			cout << r << endl;
		}
	}
	
	else
	{
		cout << "No synonyms found." << endl;
	}
}


void GtkAiksaur::createWindow()
{
	d_window_ptr = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(
		GTK_WINDOW(d_window_ptr), 
		"AbiWord Thesaurus"
	);
	
	// this makes the program exit when the window is closed.
	gtk_signal_connect(
		GTK_OBJECT(d_window_ptr), 
		"delete_event", 
		GTK_SIGNAL_FUNC(GtkAiksaur_exitCallback), 
		NULL
	);

	d_layout_ptr = gtk_vbox_new(false, 4);
	
	gtk_container_add(
		GTK_CONTAINER(d_window_ptr),
		d_layout_ptr
	);
}


void GtkAiksaur::createToolbar()
{
	d_toolbar_ptr = gtk_hbox_new(
		false, 
		4	
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

void GtkAiksaur::createReplacebar()
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
	createCancelbutton();
	createOkbutton();
}


void GtkAiksaur::createReplaceentry()
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

	gtk_box_pack_start(
		GTK_BOX(d_replacebar_ptr),
		d_replacewith_ptr,
		false,
		false,
		2
	);
}

void GtkAiksaur::createOkbutton()
{
	d_okbutton_ptr = gtk_button_new();
	d_okbutton_label_ptr = gtk_label_new("Ok");

	gtk_container_add(
		GTK_CONTAINER(d_okbutton_ptr),
		d_okbutton_label_ptr
	);

	gtk_box_pack_end(
		GTK_BOX(d_replacebar_ptr),
		d_okbutton_ptr,
		false,
		false,
		2
	);
}

void GtkAiksaur::createCancelbutton()
{
	d_cancelbutton_ptr = gtk_button_new();
	d_cancelbutton_label_ptr = gtk_label_new("Cancel");

	gtk_container_add(
		GTK_CONTAINER(d_cancelbutton_ptr),
		d_cancelbutton_label_ptr
	);
	
	gtk_box_pack_end(
		GTK_BOX(d_replacebar_ptr),
		d_cancelbutton_ptr,
		false,
		false,
		5	
	);
}

void GtkAiksaur::createBackbutton()
{
	d_backbutton_ptr = gtk_button_new();
	d_backbutton_label_ptr = gtk_label_new("Back");

	gtk_container_add(
		GTK_CONTAINER(d_backbutton_ptr),
		d_backbutton_label_ptr
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_backbutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(GtkAiksaur_backButtonCallback),
		d_backbutton_label_ptr	
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_backbutton_ptr,
		false,
		false,
		5
	);	
}


void GtkAiksaur::createForwardbutton()
{
	d_forwardbutton_ptr = gtk_button_new();
	d_forwardbutton_label_ptr = gtk_label_new("Forward");
	
	gtk_container_add(
		GTK_CONTAINER(d_forwardbutton_ptr),
		d_forwardbutton_label_ptr
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_forwardbutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(GtkAiksaur_forwardButtonCallback),
		d_forwardbutton_label_ptr	
	);
	
	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_forwardbutton_ptr,
		false,
		false,
		5
	);	

}


void GtkAiksaur::createSearchbutton()
{
	d_searchbutton_ptr = gtk_button_new();
	d_searchbutton_label_ptr = gtk_label_new("Search");
	
	gtk_container_add(
		GTK_CONTAINER(d_searchbutton_ptr),
		d_searchbutton_label_ptr
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_searchbutton_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(GtkAiksaur_searchButtonCallback),
		d_searchbutton_label_ptr	
	);

	gtk_box_pack_start(
		GTK_BOX(d_toolbar_ptr),
		d_searchbutton_ptr,
		false,
		false,
		5
	);	
}


void GtkAiksaur::createSearchbar()
{
	d_searchbar_label_ptr = gtk_label_new("  Look up:");
	d_searchbar_ptr = gtk_combo_new();

	cout << "Searchbar created: address is " << d_searchbar_ptr << endl;
	
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

static void 
GtkAiksaur_backButtonCallback(GtkWidget* w, gpointer data)
{
	cout << "Back button pressed." << endl;
}

static void 
GtkAiksaur_forwardButtonCallback(GtkWidget* w, gpointer data)
{
	cout << "Forward button pressed." << endl;
}

static void 
GtkAiksaur_searchButtonCallback(GtkWidget* w, gpointer data)
{
	GtkAiksaur *instance = GtkAiksaur::s_instance;

	instance->performSearch(
		instance->getSearchText()
	);
}

static gint
GtkAiksaur_exitCallback(GtkWidget* w, GdkEventAny* e, gpointer data)
{
	cout << "Exit button pressed." << endl;
	exit(0);
}



