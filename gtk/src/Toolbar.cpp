/*
 * AiksaurusGTK - A GTK interface to the Aiksaurus library
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

#include "Toolbar.h"
#include "Icons.h"
#include "AiksaurusGTK_picbutton.h"
#include "DialogMediator.h"
#include <gdk/gdkkeysyms.h>

namespace AiksaurusGTK_impl 
{

    Toolbar::Toolbar(DialogMediator& mediator, GtkWidget* window) throw(std::bad_alloc)
        : d_mediator(mediator), 
          d_searchbar_words(12), 
          d_ishistorymove(false), 
          d_searchhack(false),
          d_window_ptr(window)
    {
        d_tooltips_ptr = gtk_tooltips_new();
        d_toolbar_ptr = gtk_hbox_new(false,	0);

        // Create back button and menu
        d_backbutton_box_ptr = gtk_hbox_new(false, 0);
        d_backbutton_ptr = new AiksaurusGTK_picbutton(d_window_ptr, Icons::backNormal);
        d_backbutton_ptr->setHoverPicture(Icons::backHover);
        d_backbutton_ptr->addMenu(d_history.list_back(), GTK_SIGNAL_FUNC(_backMenuClicked), this);
        d_backbutton_ptr->limitVisibleOptions(10);
        _setTooltip(d_backbutton_ptr->getButton(), "Back");

        // Create forward button and menu
        d_forwardbutton_ptr = new AiksaurusGTK_picbutton(d_window_ptr, Icons::forwardNormal);
        d_forwardbutton_ptr->setHoverPicture(Icons::forwardHover);
        d_forwardbutton_ptr->addMenu(d_history.list_forward(), 
                                     GTK_SIGNAL_FUNC(_forwardMenuClicked), this);
        d_forwardbutton_ptr->limitVisibleOptions(10);
        _setTooltip(d_forwardbutton_ptr->getButton(), "Forward");


        // Create search dropdown bar.
        d_searchbar_label_ptr = gtk_label_new("  Look up:");
        d_searchbar_ptr = gtk_combo_new();
        gtk_combo_set_use_arrows(GTK_COMBO(d_searchbar_ptr), false);
        gtk_combo_disable_activate(GTK_COMBO(d_searchbar_ptr));
        _setTooltip(GTK_WIDGET(GTK_COMBO(d_searchbar_ptr)->entry), "Enter word to look up");

        // Create search button
        d_searchbutton_ptr = new AiksaurusGTK_picbutton(d_window_ptr, Icons::searchNormal);
        d_searchbutton_ptr->setHoverPicture(Icons::searchHover);
        _setTooltip(d_searchbutton_ptr->getButton(), "Find Synonyms");


        // Add all widgets to the toolbar layout box.
        gtk_box_pack_start(GTK_BOX(d_backbutton_box_ptr), d_backbutton_ptr->getButton(), 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(d_backbutton_box_ptr), d_backbutton_ptr->getMenuButton(), 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_backbutton_box_ptr, 0, 0, 4);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_forwardbutton_ptr->getButton(), 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_forwardbutton_ptr->getMenuButton(), 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_searchbar_label_ptr, 0, 0, 5);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_searchbar_ptr, 1, 1, 5);
        gtk_box_pack_start(GTK_BOX(d_toolbar_ptr), d_searchbutton_ptr->getButton(), 0, 0, 4);


        // Connect all relevant signals.
        gtk_signal_connect(GTK_OBJECT(d_backbutton_ptr->getButton()), "clicked",
                           GTK_SIGNAL_FUNC(_backClicked), this);
        gtk_signal_connect(GTK_OBJECT(d_forwardbutton_ptr->getButton()), "clicked",
                           GTK_SIGNAL_FUNC(_forwardClicked), this);
        gtk_signal_connect(GTK_OBJECT(d_searchbutton_ptr->getButton()), "clicked",
                           GTK_SIGNAL_FUNC(_searchClicked), this);
        gtk_signal_connect(GTK_OBJECT(GTK_COMBO(d_searchbar_ptr)->entry), "key-press-event",
                           GTK_SIGNAL_FUNC(_searchBarKeypress), this);
        gtk_signal_connect(GTK_OBJECT(GTK_COMBO(d_searchbar_ptr)->popwin), "hide",
                           GTK_SIGNAL_FUNC(_searchBarHide), this);
        gtk_signal_connect(GTK_OBJECT(GTK_COMBO(d_searchbar_ptr)->entry), "changed",
                           GTK_SIGNAL_FUNC(_searchBarChanged), this);

        _updateNavigation();
    }

    Toolbar::~Toolbar() throw()
    {

    }
    
    void Toolbar::_updateNavigation() throw(std::bad_alloc)
    {
        if (d_history.size_back())
            d_backbutton_ptr->enable();
        else
            d_backbutton_ptr->disable();

        if (d_history.size_forward())
            d_forwardbutton_ptr->enable();
        else
            d_forwardbutton_ptr->disable();

        _setTooltip(d_backbutton_ptr->getButton(), d_history.tip_back());
        _setTooltip(d_forwardbutton_ptr->getButton(), d_history.tip_forward());

        d_backbutton_ptr->updateMenuOptions();
        d_forwardbutton_ptr->updateMenuOptions();
    }

    void Toolbar::search(const char* str) throw(std::bad_alloc)
    {
        if (!d_ishistorymove)
            d_history.search(str);

        _updateNavigation();

        d_searchbar_words.addItem(str);
        gtk_combo_set_popdown_strings(
            GTK_COMBO(d_searchbar_ptr),
            const_cast<GList*>(d_searchbar_words.list())
        );
    }
   
    void Toolbar::_setTooltip(GtkWidget* w, const char* str) throw()
    {
        gtk_tooltips_set_tip(d_tooltips_ptr, w,	str, 0);
    }
 
    void Toolbar::focus() throw()
    {
        gtk_window_set_focus(GTK_WINDOW(d_window_ptr), GTK_COMBO(d_searchbar_ptr)->entry);
    }
    
    const char* Toolbar::getText() const throw()
    {
        return gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(d_searchbar_ptr)->entry));
    }

    GtkWidget* Toolbar::getToolbar() throw()
    {
        return d_toolbar_ptr;
    }


    
    void Toolbar::_backClicked(GtkWidget* w, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);
        tb->d_history.move_back();
        tb->d_ishistorymove = true;
        tb->d_mediator.eventSearch( tb->d_history.current() );
        tb->d_ishistorymove = false;
    }

    void Toolbar::_backMenuClicked(GList* element, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);
        tb->d_history.move_back_to(element);
        tb->d_ishistorymove = true;
        tb->d_mediator.eventSearch( tb->d_history.current() );
        tb->d_ishistorymove = false;
    }

    void Toolbar::_forwardClicked(GtkWidget* w, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);
        tb->d_history.move_forward();
        tb->d_ishistorymove = true;
        tb->d_mediator.eventSearch( tb->d_history.current() );
        tb->d_ishistorymove = false;
    }

    void Toolbar::_forwardMenuClicked(GList* element, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);
        tb->d_history.move_forward_to(element);
        tb->d_ishistorymove = true;
        tb->d_mediator.eventSearch( tb->d_history.current() );
        tb->d_ishistorymove = false;
    }
    
    void Toolbar::_searchBarChanged(GtkWidget* w, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);

        if (GTK_WIDGET_VISIBLE(GTK_COMBO(tb->d_searchbar_ptr)->popwin))
            tb->d_searchhack = true;
    }   
    
    void Toolbar::_searchBarHide(GtkWidget* w, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);

        if (tb->d_searchhack)
            tb->d_mediator.eventSearch( tb->getText() );

        tb->d_searchhack = false;
    }

    void Toolbar::_searchBarKeypress(GtkWidget* w, GdkEventKey* k, gpointer data) throw()
    {
        if (k->keyval == GDK_Return)
            _searchClicked(w, data);
    }

    void Toolbar::_searchClicked(GtkWidget* w, gpointer data) throw()
    {
        Toolbar* tb = static_cast<Toolbar*>(data);
        tb->d_mediator.eventSearch( tb->getText() );
    }

}
