
#include "gtk/gtk.h"
#include "gtkAiksaur.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static
void closeTestprogram(GtkWidget* w, GdkEventAny *e, gpointer data)
{
	cout << "Exit pressed." << endl;
	exit(0);
}

static 
void searchButton(GtkWidget* w, gpointer data)
{
	cout << "Search pressed." << endl;
	GtkWidget* entry = static_cast<GtkWidget*>(data);

	const char* text = gtk_entry_get_text(
		GTK_ENTRY(entry)
	);
	
	cout << "Searched for " << text << endl;
		
	cout << "User chose: " << ActivateThesaurus(text) << endl;
}

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	// this creates our main window.
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// this hooks up the close-box on the window's border to actually do something.
	gtk_signal_connect(
		GTK_OBJECT(window),
		"delete-event",
		GTK_SIGNAL_FUNC(closeTestprogram),
		NULL
	);
	
	// this sets the title of our main window.
	gtk_window_set_title(
		GTK_WINDOW(window), 
		"AiksaurusGTK Test Program"
	);
	
	// this is a layout widget, to which our other widgets will be added.
	GtkWidget* box = gtk_hbox_new(false, 3);
	
	// this adds the layout widget to the window.
	gtk_container_add(
		GTK_CONTAINER(window),
		box
	);
	
	// this is just our text label.
	GtkWidget* label = gtk_label_new("Look up: ");
	
	// this adds the text label to the layout widget.
	gtk_box_pack_start(
		GTK_BOX(box),
		label,
		false,
		false,
		3
	);

	// this is our input box.
	GtkWidget* entry = gtk_entry_new();

	// this adds the input box to the layout widget.
	gtk_box_pack_start(
		GTK_BOX(box),
		entry,
		false,
		false,
		3
	);

	// this is our ok button.
	GtkWidget* okbutton = gtk_button_new_with_label("  Search  ");
	
	// this hook sup our ok button to the search callback.
	gtk_signal_connect(
		GTK_OBJECT(okbutton),
		"clicked",
		GTK_SIGNAL_FUNC(searchButton),
		entry
	);
	
	// this adds the ok button to our layout widget.
	gtk_box_pack_start(
		GTK_BOX(box),
		okbutton,
		false,
		false,
		3
	);
	
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
};
