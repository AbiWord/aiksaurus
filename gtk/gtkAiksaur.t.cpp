#include "gtk/gtk.h"
#include "gtkAiksaur.h"

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);

	ActivateThesaurus("fool");

	return 0;
};
