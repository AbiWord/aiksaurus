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
#include <iostream>
using namespace std;



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Creation, Menu Addition, Hover Icon Setting                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

AiksaurusGTK_picbutton::AiksaurusGTK_picbutton(GtkWidget *window, const char** normal)
{
	d_window_ptr = window;
	d_style_ptr = gtk_widget_get_style(window);
    d_menu_options_ptr = NULL;
    d_menu_ptr = NULL;
    
	d_enabled = true;
	
	d_menushowing = false;
	d_hashover = false;
	d_hasmenu = false;
	d_mouseover = false;
	
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


AiksaurusGTK_picbutton::~AiksaurusGTK_picbutton()
{
    // TO DO: what if this is null?
    gtk_widget_destroy(d_menu_ptr);

    if (d_menu_options_ptr)
        delete d_menu_options_ptr;
}


void
AiksaurusGTK_picbutton::setHoverPicture(const char** hover)
{
	d_hashover = true;
	
	d_hoverpixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_hovermask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)hover
	);

	gtk_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"enter",
		GTK_SIGNAL_FUNC(cbHover),
		this
	);

	gtk_signal_connect(
		GTK_OBJECT(d_button_ptr),
		"leave",
		GTK_SIGNAL_FUNC(cbUnhover),
		this
	);

	handleRelief();
}


void
AiksaurusGTK_picbutton::addMenu(GtkSignalFunc onClick, gpointer onClickData)
{
    d_onclick_function = onClick;
    d_onclick_data = onClickData;
    
	d_hasmenu = true;

	d_menu_button_ptr = gtk_button_new();
	gtk_widget_show(d_menu_button_ptr);

	GTK_WIDGET_UNSET_FLAGS(
		d_menu_button_ptr,
		GTK_CAN_FOCUS
	);

	d_menu_pixmap_ptr = gdk_pixmap_create_from_xpm_d(
		d_window_ptr->window,
		&d_menu_mask_ptr,
		&d_style_ptr->bg[GTK_STATE_NORMAL],
		(gchar**)s_downArrow
	);
	
	d_menu_pixmap_widget_ptr = gtk_pixmap_new(
		d_menu_pixmap_ptr,
		d_menu_mask_ptr
	);
	
	gtk_widget_show(d_menu_pixmap_widget_ptr);
	
	gtk_container_add(
		GTK_CONTAINER(d_menu_button_ptr),
		d_menu_pixmap_widget_ptr
	);
	
	gtk_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"enter",
		GTK_SIGNAL_FUNC(cbHover),
		this
	);

	gtk_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"leave",
		GTK_SIGNAL_FUNC(cbUnhover),
		this
	);
	
	handleRelief();

	gtk_signal_connect(
		GTK_OBJECT(d_menu_button_ptr),
		"clicked",
		GTK_SIGNAL_FUNC(cbPopMenu),
		this
	);

    menuCreate();
    
    d_menu_options_ptr = new AiksaurusGTK_strlist;
}


GtkWidget* 
AiksaurusGTK_picbutton::getButton()
{
	return d_button_ptr;
}


GtkWidget*
AiksaurusGTK_picbutton::getMenuButton()
{
	return d_menu_button_ptr;
}


AiksaurusGTK_strlist& 
AiksaurusGTK_picbutton::getMenuOptions()
{
	return *d_menu_options_ptr;
}


void
AiksaurusGTK_picbutton::menuCreate()
{
    if (d_menu_ptr != NULL)
        gtk_widget_destroy(d_menu_ptr);

    d_menu_ptr = gtk_menu_new();
	
    gtk_widget_show(d_menu_ptr);
	
	gtk_signal_connect(
		GTK_OBJECT(d_menu_ptr),
		"selection-done",
		GTK_SIGNAL_FUNC(cbSelectionDone),
		this
	);
}


void
AiksaurusGTK_picbutton::updateMenuOptions()
{
    menuCreate();
    
    GList* l = const_cast<GList*>(d_menu_options_ptr->list());

    while(l != NULL)
    {
        char* item = static_cast<char*>(l->data);

        GtkWidget* option = gtk_menu_item_new_with_label(item);
        gtk_widget_show(option);
        
        gtk_menu_append(GTK_MENU(d_menu_ptr), option);

        gtk_signal_connect(
            GTK_OBJECT(option),
            "activate",
            GTK_SIGNAL_FUNC(cbMenuActivate),
            this 
        );
        
        l = l->next;
    }
}


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Enabling and Disabling Support                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void 
AiksaurusGTK_picbutton::disable()
{
    bool mousestate = d_mouseover;
    d_mouseover = false;
	handleRelief();
    d_mouseover = mousestate;
    
    d_enabled = false;
	
	gtk_widget_set_sensitive(
		d_button_ptr,
		false
	);

	if (d_hasmenu)
	{
		gtk_widget_set_sensitive(
			d_menu_button_ptr,
			false
		);
	}
}


void
AiksaurusGTK_picbutton::enable()
{
	d_enabled = true;

	gtk_widget_set_sensitive(
		d_button_ptr,
		true
	);

	if (d_hasmenu)
	{
		gtk_widget_set_sensitive(
			d_menu_button_ptr,
			true	
		);
	}

    handleRelief();
}





//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Hover Effect                                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void 
AiksaurusGTK_picbutton::handleRelief()
{
	const GtkReliefStyle off = GTK_RELIEF_NONE;
	const GtkReliefStyle on = GTK_RELIEF_HALF;
	
	GtkReliefStyle d_border_state = off;
	
	if (!d_hashover)
	{
		d_border_state = on;
	}
	
	else 
	{
		if (d_menushowing || d_mouseover)
		{
			d_border_state = on;
		
			gtk_pixmap_set(
				GTK_PIXMAP(d_pixmap_ptr),
				d_hoverpixmap_ptr,
				d_hovermask_ptr
			);
		}

		else
		{
			gtk_pixmap_set(
				GTK_PIXMAP(d_pixmap_ptr),
				d_normalpixmap_ptr,
				d_normalmask_ptr
			);
		}
	}
	
	gtk_button_set_relief(
		GTK_BUTTON(d_button_ptr),
		d_border_state
	);

	if (d_hasmenu)
	{
		gtk_button_set_relief(
			GTK_BUTTON(d_menu_button_ptr),
			d_border_state
		);
	}
}


void
AiksaurusGTK_picbutton::hover()
{
	d_mouseover = true;
	handleRelief();
}


void 
AiksaurusGTK_picbutton::unhover()
{
	d_mouseover = false;
	handleRelief();
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Drop-Down Menu                                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void 
AiksaurusGTK_picbutton::popMenu()
{
	d_menushowing = true;
	
	gtk_menu_popup(
		GTK_MENU(d_menu_ptr),
		NULL,
		NULL,
		cbPopupFunction,
		this,
		0,
		0
	);
}


void 
AiksaurusGTK_picbutton::popupFunction(int* x, int* y)
{
	gdk_window_get_origin(d_button_ptr->window, x, y);
	(*y) += d_button_ptr->allocation.height;
}


void 
AiksaurusGTK_picbutton::selectionDone()
{
	d_menushowing = false;

	handleRelief();
}

void
AiksaurusGTK_picbutton::menuActivate(GtkMenuItem* item)
{
    char* s;
    gtk_label_get(GTK_LABEL(GTK_BIN(item)->child), &s);
    d_onclick_function(s, d_onclick_data);
}



//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   Callback Functions                                                 //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

void AiksaurusGTK_picbutton::cbHover(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->hover();
}

void AiksaurusGTK_picbutton::cbUnhover(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->unhover();
}

void AiksaurusGTK_picbutton::cbPopMenu(GtkWidget* w, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->popMenu();
}

void AiksaurusGTK_picbutton::cbPopupFunction(GtkMenu* menu, int* x, int* y, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->popupFunction(x, y);
}

void AiksaurusGTK_picbutton::cbSelectionDone(GtkMenuShell* menushell, gpointer data)
{
	static_cast<AiksaurusGTK_picbutton*>(data)->selectionDone();
}

void AiksaurusGTK_picbutton::cbMenuActivate(GtkMenuItem* item, gpointer data)
{
    static_cast<AiksaurusGTK_picbutton*>(data)->menuActivate(item);
}


//////////////////////////////////////////////////////////////////////////
//                                                                      //
//   XPM Pictures                                                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

const char *AiksaurusGTK_picbutton::s_downArrow[]={
"11 16 2 1",
"# c #000000",
". c None",
"...........",
"...........",
"...........",
"...........",
"...........",
"...........",
"..#######..",
"...#####...",
"....###....",
".....#.....",
"...........",
"...........",
"...........",
"...........",
"...........",
"..........."};

