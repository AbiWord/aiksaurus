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

#include "AiksaurusGTK_picbutton.h"

void
AiksaurusGTK_picbutton::cbEntered(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->hover();
}


void 
AiksaurusGTK_picbutton::cbLeft(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->unhover();
}


void
AiksaurusGTK_picbutton::hover()
{
	if (d_enabled)
	{
		gtk_pixmap_set(
			GTK_PIXMAP(d_pixmap_ptr),
			d_hoverpixmap_ptr,
			d_hovermask_ptr
		);
	}
}

void 
AiksaurusGTK_picbutton::unhover()
{
	if (d_enabled)
	{
		gtk_pixmap_set(
			GTK_PIXMAP(d_pixmap_ptr),
			d_normalpixmap_ptr,
			d_normalmask_ptr
		);
	}
}


void 
AiksaurusGTK_picbutton::disable()
{
	d_enabled = false;

	gtk_widget_set_sensitive(
		d_button_ptr,
		false
	);
}


void
AiksaurusGTK_picbutton::enable()
{
	d_enabled = true;

	gtk_widget_set_sensitive(
		d_button_ptr,
		true
	);
}


void
AiksaurusGTK_picbutton::setHoverPicture(const char** hover)
{
	gtk_button_set_relief(
		GTK_BUTTON(d_button_ptr),
		GTK_RELIEF_NONE
	);
	
	d_hoverpixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_hovermask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)hover
	);

	gtk_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"enter",
		GTK_SIGNAL_FUNC(cbEntered),
		this
	);

	gtk_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"leave",
		GTK_SIGNAL_FUNC(cbLeft),
		this
	);
}


AiksaurusGTK_picbutton::AiksaurusGTK_picbutton(GtkWidget *window, const char** normal)
{
	d_window_ptr = window;
	d_style_ptr = gtk_widget_get_style(window);
	
	d_enabled = true;
	d_button_ptr = gtk_button_new();

	gtk_widget_show(d_button_ptr);

	GTK_WIDGET_UNSET_FLAGS(
		d_button_ptr, 
		GTK_CAN_FOCUS
	);
	
	d_normalpixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_normalmask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)normal
	);
	

	d_pixmap_ptr = gtk_pixmap_new(
		d_normalpixmap_ptr,
		d_normalmask_ptr
	);

	gtk_widget_show(d_pixmap_ptr);
	
	gtk_container_add(
		GTK_CONTAINER(d_button_ptr),
		d_pixmap_ptr
	);
}


GtkWidget* AiksaurusGTK_picbutton::getButton()
{
	return d_button_ptr;
}



