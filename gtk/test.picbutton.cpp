#include "AiksaurusGTK_picbutton.h"
#include <iostream>
using namespace std;

static const char *back_green[]={
"20 16 6 1",
"a c #005d00",
"# c #009900",
"c c #00ce00",
"b c #00ff00",
"d c #31ce00",
". c None",
"....................",
"....................",
"....................",
"........#a..........",
".......#ba..........",
"......#bba#####a....",
".....#bbccccccca....",
"....#bbcddddddca....",
"....a#ccccccccca....",
".....a#c#######a....",
"......a##aaaaaaa....",
".......a#a..........",
"........aa..........",
"....................",
"....................",
"...................."};

static const char *back_gray[]={
"20 16 5 1",
"a c #4a484a",
"# c #737573",
"c c #a4a1a4",
"b c #cdcacd",
". c None",
"....................",
"....................",
"....................",
"........#a..........",
".......#ba..........",
"......#bba#####a....",
".....#bbccccccca....",
"....#bbcccccccca....",
"....a#ccccccccca....",
".....a#c#######a....",
"......a##aaaaaaa....",
".......a#a..........",
"........aa..........",
"....................",
"....................",
"...................."};


AiksaurusGTK_strlist MenuOptions;

void
disablepb(GtkWidget* w, gpointer data)
{
	AiksaurusGTK_picbutton* pb = static_cast<AiksaurusGTK_picbutton*>(data);
	pb->disable();
    MenuOptions.pop_front();
    pb->updateMenuOptions();
}

void 
enablepb(GtkWidget* w, gpointer data)
{
	AiksaurusGTK_picbutton* pb = static_cast<AiksaurusGTK_picbutton*>(data);
	pb->enable();
}

void
menuselection(GList* selection, gpointer data)
{
    char* x = static_cast<char*>(selection->data);
    cout << "menuselection(" << x << ") called." << endl;
}


int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(
		GTK_WINDOW_TOPLEVEL
	);

	gtk_widget_show(window);

	GtkWidget *layout = gtk_hbox_new(false, 4);
	gtk_widget_show(layout);
	
	gtk_container_add(
		GTK_CONTAINER(window),
		layout
	);
	
    cout << "Window created." << endl;
    
	AiksaurusGTK_picbutton pb(window, back_gray);
	pb.setHoverPicture(back_green);
	pb.addMenu(MenuOptions, GTK_SIGNAL_FUNC(menuselection), &pb);

    cout << "Menu added." << endl;
    MenuOptions.push_back("Menu option 1");
    MenuOptions.push_back("Menu option 2");
    MenuOptions.push_back("Menu option 3");
    MenuOptions.push_back("Menu option 4");
    pb.updateMenuOptions();
    
	GtkWidget *btnbox = gtk_hbox_new(false, 0);
	gtk_widget_show(btnbox);
	
	gtk_box_pack_start(
		GTK_BOX(btnbox), 
		pb.getButton(),
		false,
		false,
		0
	);
	
	gtk_box_pack_start(
		GTK_BOX(btnbox),
		pb.getMenuButton(),
		false,
		false,
		0
	);
	
	
	gtk_box_pack_start(
		GTK_BOX(layout),
		btnbox,
		false,
		false,
		4
	);

    cout << "Creating enable button." << endl;    
	GtkWidget* enablebtn = gtk_button_new_with_label("Enable");
	gtk_widget_show(enablebtn);
    gtk_signal_connect(
		GTK_OBJECT(enablebtn),
    	"clicked",
		GTK_SIGNAL_FUNC(enablepb),
		&pb
	);

    cout << "Creating disable button." << endl;
	GtkWidget* disablebtn = gtk_button_new_with_label("Disable");
	gtk_widget_show(disablebtn);
	gtk_signal_connect(
		GTK_OBJECT(disablebtn),
		"clicked",
		GTK_SIGNAL_FUNC(disablepb),
		&pb
	);

	gtk_box_pack_start(
		GTK_BOX(layout),
		enablebtn,
		false,
		false,
		4
	);

	gtk_box_pack_start(
		GTK_BOX(layout),
		disablebtn,
		false,
		false,
		4
	);

    cout << "About to enter gtk_main()" << endl;
    
	gtk_main();

	return 0;
}

