#ifndef INCLUDED_GPL_JARED_AIKSAURUSGTK_PICBUTTON_H
#define INCLUDED_GPL_JARED_AIKSAURUSGTK_PICBUTTON_H

#include <glib.h>
#include <gtk/gtk.h>

class AiksaurusGTK_picbutton
{
	private:

		GtkWidget* d_window_ptr;
		GtkWidget* d_button_ptr;

		GtkWidget* d_pixmap_ptr;
		GtkStyle* d_style_ptr;
	
		GdkPixmap* d_normalpixmap_ptr;
		GdkBitmap* d_normalmask_ptr;
		
		GdkPixmap* d_hoverpixmap_ptr;
		GdkBitmap* d_hovermask_ptr;
		
		GdkPixmap* d_disabledpixmap_ptr;
		GdkBitmap* d_disabledmask_ptr;
		
		bool d_enabled;

		static void cbEntered(GtkWidget* w, gpointer data);
		static void cbLeft(GtkWidget* w, gpointer data);
	
		void hover();
		void unhover();
		
	public:

		AiksaurusGTK_picbutton(GtkWidget *window, const char** normal);
		
		void setHoverPicture(const char** hover);
		void setDisabledPicture(const char** disabled);
		
		void disable();
		void enable();

		GtkWidget* getButton();
};

#endif // INCLUDED_GPL_JARED_AIKSAURUSGTK_PICBUTTON_H
