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
	
		// The main dialog window.
		GtkWidget* d_window_ptr;

		// The main tool bar.
		GtkWidget* d_toolbar_ptr;
	
		// Back, forward, and search buttons.
		GtkWidget* d_backbutton_ptr;
		GtkWidget* d_backbutton_label_ptr;
		GtkWidget* d_forwardbutton_ptr;
		GtkWidget* d_forwardbutton_label_ptr;
		GtkWidget* d_searchbutton_ptr;
		GtkWidget* d_searchbutton_label_ptr;
	
		// User-editable "search bar" and "Look up:" label.
		GtkWidget* d_searchbar_ptr;
		GtkWidget* d_searchbar_label_ptr;

		// Component creation functions, actually build the UI.
		void createWindow();
		void createToolbar();
		void createBackbutton();
		void createForwardbutton();	
		void createSearchbutton();
		void createSearchbar();
		
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
		GtkAiksaur::s_instance = new GtkAiksaur();
	}

	// To do: run a search for 'search'.
}



GtkAiksaur::GtkAiksaur()
{
	createWindow();
	createToolbar();
	
	gtk_widget_show_all(d_window_ptr);
	gtk_main();
}


const char* GtkAiksaur::getSearchText()
{
	cout << "GetSearchText called." << endl;
	return "";
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
}


void GtkAiksaur::createToolbar()
{
	d_toolbar_ptr = gtk_toolbar_new(
		GTK_ORIENTATION_HORIZONTAL, 
		GTK_TOOLBAR_ICONS
	);

	createBackbutton();
	createForwardbutton();
	createSearchbar();
	createSearchbutton();
	
	gtk_container_add(
		GTK_CONTAINER(d_window_ptr), 		
		d_toolbar_ptr
	);
}


void GtkAiksaur::createBackbutton()
{
	d_backbutton_ptr = gtk_button_new();
	d_backbutton_label_ptr = gtk_label_new("<-");

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

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_backbutton_ptr,
		"Previous Search",
		"Previous Search"
	);	
}


void GtkAiksaur::createForwardbutton()
{
	d_forwardbutton_ptr = gtk_button_new();
	d_forwardbutton_label_ptr = gtk_label_new("->");
	
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

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_forwardbutton_ptr,
		"Next Search",
		"Next Search"
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

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_searchbutton_ptr,
		"Perform Search",
		"Perform Search"
	);	
}


void GtkAiksaur::createSearchbar()
{
	d_searchbar_label_ptr = gtk_label_new("  Look up:");
	d_searchbar_ptr = gtk_entry_new();

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_searchbar_label_ptr,
		NULL,
		NULL
	);

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_searchbar_ptr,
		NULL,
		NULL
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
	cout << "Search button pressed." << endl;
}

static gint
GtkAiksaur_exitCallback(GtkWidget* w, GdkEventAny* e, gpointer data)
{
	cout << "Exit button pressed." << endl;
	exit(0);
}



