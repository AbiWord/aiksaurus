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
		
		// Icons for the tool bar.
		static const char* s_forwardIcon[];
		  GdkPixmap* d_forwardicon_pic_ptr;
		  GtkWidget* d_forwardicon_ptr;
		static const char* s_backIcon[];
		  GdkPixmap* d_backicon_pic_ptr;
		  GtkWidget* d_backicon_ptr;

		  
		// A listbox to list our synonyms.
		GtkWidget* d_wordlist_ptr;

		// The replace/ok/cancel bar and associated widgets
		GtkWidget *d_replacebar_ptr;
		  GtkWidget *d_replacebutton_ptr;
		  GtkWidget *d_replacebutton_label_ptr;
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
	
	gtk_clist_set_column_auto_resize(
		GTK_CLIST(d_wordlist_ptr),
		0, 
		false
	);

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
	d_replacebutton_ptr = gtk_button_new();
	d_replacebutton_label_ptr = gtk_label_new("Replace");

	gtk_container_add(
		GTK_CONTAINER(d_replacebutton_ptr),
		d_replacebutton_label_ptr
	);

	gtk_box_pack_end(
		GTK_BOX(d_replacebar_ptr),
		d_replacebutton_ptr,
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
	GdkBitmap *mask;
	GtkStyle *style = gtk_widget_get_style(d_window_ptr);
	
	d_backicon_pic_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&mask,
		&style->bg[GTK_STATE_NORMAL],
		(gchar**)s_backIcon
	);
	
	d_backicon_ptr = gtk_pixmap_new(
		d_backicon_pic_ptr,
		mask
	);
	
	d_backbutton_ptr = gtk_button_new();
	//d_backbutton_label_ptr = gtk_label_new("Back");

	gtk_container_add(
		GTK_CONTAINER(d_backbutton_ptr),
		d_backicon_ptr
	);
	
	//gtk_container_add(
	//	GTK_CONTAINER(d_backbutton_ptr),
	//	d_backbutton_label_ptr
	//);
	
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





//////////////////////////////////////////////////////////////////////////
//
//   gtkAiksaur Icons
//
//////////////////////////////////////////////////////////////////////////

const char *GtkAiksaur::s_forwardIcon[] = {
"16 16 47 1",
" 	g None",
".	g #000000",
"+	g #0E0E0E",
"@	g #424242",
"#	g #141414",
"$	g #7D7D7D",
"%	g #444444",
"&	g #202020",
"*	g #1F1F1F",
"=	g #494949",
"-	g #A9A9A9",
";	g #6E6E6E",
">	g #484848",
",	g #646464",
"'	g #6D6D6D",
")	g #797979",
"!	g #747474",
"~	g #757575",
"{	g #787878",
"]	g #B2B2B2",
"^	g #464646",
"/	g #191919",
"(	g #171717",
"_	g #8E8E8E",
":	g #9A9A9A",
"<	g #AAAAAA",
"[	g #727272",
"}	g #111111",
"|	g #959595",
"1	g #878787",
"2	g #A5A5A5",
"3	g #EAEAEA",
"4	g #989898",
"5	g #3F3F3F",
"6	g #161616",
"7	g #B0B0B0",
"8	g #E3E3E3",
"9	g #FBFBFB",
"0	g #CCCCCC",
"a	g #B5B5B5",
"b	g #FCFCFC",
"c	g #393939",
"d	g #3E3E3E",
"e	g #ECECEC",
"f	g #404040",
"g	g #020202",
"h	g #323232",
"                ",
"       .        ",
"       .+       ",
"       .@#      ",
"       .$%#     ",
"  ..&&*=-;>#    ",
"  .,')!~{];^/   ",
"  (_:<<_[{-;>}  ",
"  (|[[[[[12345  ",
"  6789801ab4%   ",
"  @@@@@c2b4d    ",
"       .e4f     ",
"       g4@      ",
"       hd       ",
"       @        ",
"                "
};


const char* GtkAiksaur::s_backIcon[] = {
"16 16 47 1",
" 	g None",
".	g #424242",
"+	g #3E3E3E",
"@	g #323232",
"#	g #989898",
"$	g #020202",
"%	g #404040",
"&	g #ECECEC",
"*	g #000000",
"=	g #FCFCFC",
"-	g #A5A5A5",
";	g #393939",
">	g #444444",
",	g #B5B5B5",
"'	g #878787",
")	g #CCCCCC",
"!	g #E3E3E3",
"~	g #FBFBFB",
"{	g #B0B0B0",
"]	g #161616",
"^	g #3F3F3F",
"/	g #EAEAEA",
"(	g #727272",
"_	g #959595",
":	g #171717",
"<	g #111111",
"[	g #484848",
"}	g #6E6E6E",
"|	g #A9A9A9",
"1	g #787878",
"2	g #8E8E8E",
"3	g #AAAAAA",
"4	g #9A9A9A",
"5	g #191919",
"6	g #464646",
"7	g #B2B2B2",
"8	g #757575",
"9	g #747474",
"0	g #797979",
"a	g #6D6D6D",
"b	g #646464",
"c	g #141414",
"d	g #494949",
"e	g #1F1F1F",
"f	g #202020",
"g	g #7D7D7D",
"h	g #0E0E0E",
"                ",
"        .       ",
"       +@       ",
"      .#$       ",
"     %#&*       ",
"    +#=-;.....  ",
"   >#=,')!~!{]  ",
"  ^#/-'(((((_:  ",
"  <[}|1(23342:  ",
"   56}71890ab*  ",
"    c[}|deff**  ",
"     c>g*       ",
"      c.*       ",
"       h*       ",
"        *       ",
"                "};
