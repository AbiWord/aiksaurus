#include <AikSaurus.h>
#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
using namespace std;





//
// Callback Function Prototypes -----------------------------------------------
//   These are the callback functions used by the gtkAiksaur class to 
//   handle the different actions that the user can take.
//

static gint 
gaik_exitCallback(GtkWidget* w, GdkEventAny* e, gpointer data);
	
static void 
gaik_backButtonCallback(GtkWidget* w, gpointer data);
	
static void 
gaik_forwardButtonCallback(GtkWidget* w, gpointer data);
	
static void 
gaik_searchButtonCallback(GtkWidget* w, gpointer data);




// 
// gtkAiksaur Class -----------------------------------------------------------
//   This is the main class that implements the thesaurus dialog.  
//
	
class gtkAiksaur
{
	friend void gaik_searchButtonCallback(GtkWidget*w, gpointer data);
	
	private:
		
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
		
	public:
		gtkAiksaur();	


};

gtkAiksaur::gtkAiksaur()
{
	createWindow();
	createToolbar();
	
	gtk_widget_show_all(d_window_ptr);
	gtk_main();
}

const char* gtkAiksaur::getSearchText()
{
	cout << "GetSearchText called." << endl;
	return "";
}

void gtkAiksaur::createWindow()
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
		GTK_SIGNAL_FUNC(gaik_exitCallback), 
		NULL
	);
}

void gtkAiksaur::createToolbar()
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

void gtkAiksaur::createBackbutton()
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
		GTK_SIGNAL_FUNC(gaik_backButtonCallback),
		d_backbutton_label_ptr	
	);

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_backbutton_ptr,
		"Previous Search",
		"Previous Search"
	);	
}

void gtkAiksaur::createForwardbutton()
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
		GTK_SIGNAL_FUNC(gaik_forwardButtonCallback),
		d_forwardbutton_label_ptr	
	);

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_forwardbutton_ptr,
		"Next Search",
		"Next Search"
	);	
}

void gtkAiksaur::createSearchbutton()
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
		GTK_SIGNAL_FUNC(gaik_searchButtonCallback),
		d_searchbutton_label_ptr	
	);

	gtk_toolbar_append_widget(
		GTK_TOOLBAR(d_toolbar_ptr),
		d_searchbutton_ptr,
		"Perform Search",
		"Perform Search"
	);	
}

void gtkAiksaur::createSearchbar()
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
gaik_backButtonCallback(GtkWidget* w, gpointer data)
{
	cout << "Back button pressed." << endl;
}

static void 
gaik_forwardButtonCallback(GtkWidget* w, gpointer data)
{
	cout << "Forward button pressed." << endl;
}

static void 
gaik_searchButtonCallback(GtkWidget* w, gpointer data)
{
	cout << "Search button pressed." << endl;
}

static gint
gaik_exitCallback(GtkWidget* w, GdkEventAny* e, gpointer data)
{
	cout << "Exit button pressed." << endl;
	exit(0);
}

















gtkAiksaur* ThesaurusDialogPointer = NULL;

//
// Interface Functions
// -------------------
//   These functions form the programmatic interface to gtkAiksaur.
//   They are the only functions that external programs should call.
//   
const char* ActivateThesaurus(const char* search)
{
	if (ThesaurusDialogPointer == NULL)
	{
		ThesaurusDialogPointer = new gtkAiksaur();
	}

	// to do: update thesaurus to search for word 'search'.
}


