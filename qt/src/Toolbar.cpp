/*
 * AiksaurusQT - A QT interface to the Aiksaurus library
 * Copyright (C) 2001-2002 by Jared Davis
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
 *
 */

#include "Toolbar.h"

#ifndef INCLUDED_AIKSAURUS_QT_HOVERBUTTON_H
    #include "HoverButton.h"
#endif

#ifndef INCLUDED_AIKSAURUS_QT_MENUBUTTON_H
    #include "MenuButton.h"
#endif

#ifndef INCLUDED_AIKSAURUS_QT_ICONS_H
    #include "Icons.h"
#endif

#ifndef QPUSHBUTTON_H
    #include <qpushbutton.h>
#endif

#ifndef QPOPUPMENU_H
    #include <qpopupmenu.h>
#endif

#ifndef QCOMBOBOX_H
    #include <qcombobox.h>
#endif

#ifndef QLINEEDIT_H
    #include <qlineedit.h>
#endif

#ifndef QLAYOUT_H
    #include <qlayout.h>
#endif

#ifndef QLABEL_H
    #include <qlabel.h>
#endif


namespace AiksaurusQT_impl
{

    //
    // Toolbar::Toolbar()
    //  Create a toolbar with a parent and a mediator to send
    //  events to.
    //
    Toolbar::Toolbar(QWidget* parent)
        : QWidget(parent),
          d_ishistorymove(false),
          d_layout_ptr(0),
          d_backbutton_ptr(0),
          d_forwardbutton_ptr(0),
          d_searchfor_ptr(0),
          d_searchbar_ptr(0),
          d_searchbutton_ptr(0)
    {
        using namespace Icons;

        try
        {
            d_layout_ptr = new QHBoxLayout(this, 0, 2);
            d_backbutton_ptr = new MenuButton(this, backHover, backNormal);
            d_forwardbutton_ptr = new MenuButton(this, forwardHover, forwardNormal);
            d_searchfor_ptr = new QLabel("Look up: ", this);
            d_searchbar_ptr = new QComboBox(true, this);
            d_searchbutton_ptr = new HoverButton(this, searchHover, searchNormal);

            d_searchbar_ptr->setMinimumSize(160, 1);
            d_layout_ptr->addSpacing(4);
            d_layout_ptr->addWidget(d_backbutton_ptr);
            d_layout_ptr->addWidget(d_forwardbutton_ptr);
            d_layout_ptr->addSpacing(10);
            d_layout_ptr->addWidget(d_searchfor_ptr);
            d_layout_ptr->addWidget(d_searchbar_ptr, 1);
            d_layout_ptr->addWidget(d_searchbutton_ptr);
            d_layout_ptr->addSpacing(4);

            connect(d_searchbutton_ptr, SIGNAL(clicked()),
                    this, SLOT(_searchClicked()));

            connect(d_backbutton_ptr->getButton(), SIGNAL(clicked()),
                    this, SLOT(_backClicked()));

            connect(d_forwardbutton_ptr->getButton(), SIGNAL(clicked()),
                    this, SLOT(_forwardClicked()));

            connect(d_searchbar_ptr, SIGNAL(activated(int)),
                    this, SLOT(_searchClicked()));
        }

        catch(...)
        {
            _destruct();
            throw;
        }
    }


    //
    // Toolbar::~Toolbar()
    //   Destroy all of our widgets.
    //
    Toolbar::~Toolbar()
    {
        _destruct();
    }


    //
    // Toolbar::_destruct()
    //   Basically our destructor
    //
    void Toolbar::_destruct()
    {
        delete d_layout_ptr;
        delete d_backbutton_ptr;
        delete d_forwardbutton_ptr;
        delete d_searchfor_ptr;
        delete d_searchbar_ptr;
        delete d_searchbutton_ptr;
    }


    //
    // Toolbar::_backClicked()
    //   Move back in history and trigger a search event.
    //
    void Toolbar::_backClicked()
    {
        d_history.moveBack();
        d_ishistorymove = true;
        emit newSearch(d_history.getCurrent().getText());
        d_ishistorymove = false;
    }


    //
    // Toolbar::_forwardClicked()
    //   Move forward in history and trigger a search event.
    //
    void Toolbar::_forwardClicked()
    {
        d_history.moveForward();
        d_ishistorymove = true;
        emit newSearch(d_history.getCurrent().getText());
        d_ishistorymove = false;
    }


    //
    // Toolbar::_backMenu()
    //   Move back in history until we find the menu element id.
    //
    void Toolbar::_backMenu(int id)
    {
        while(d_history.getCurrent().getId() != id)
            d_history.moveBack();

        d_ishistorymove = true;
        emit newSearch(d_history.getCurrent().getText());
        d_ishistorymove = false;
    }


    //
    // Toolbar::_forwardMenu()
    //   Move forward in history until we find the menu element id.
    //
    void Toolbar::_forwardMenu(int id)
    {
        while(d_history.getCurrent().getId() != id)
            d_history.moveForward();

        d_ishistorymove = true;
        emit newSearch(d_history.getCurrent().getText());
        d_ishistorymove = false;
    }


    //
    // Toolbar::_searchClicked()
    //   Search button was clicked or return was pressed.  Trigger
    //   a new search event and search for the new word.
    //
    void Toolbar::_searchClicked()
    {
        // only search if this word is new.
        if (d_searchbar_ptr->currentText() != d_history.getCurrent().getText())
            emit newSearch(d_searchbar_ptr->currentText());
    }


    //
    // Toolbar::doSearch()
    //   Executed when we actually need to perform the search.  This consists
    //   mainly of updating our history and ensuring that all our buttons are
    //   showing the right state.
    //
    void Toolbar::doSearch(const char* word)
    {
        // every search performed gets a unique id which we can track
        // it by.  this simply starts numbering at 0 and counts up.
        static int search_id = 0;

        if (!d_ishistorymove)
        {
            // not a history move -- add this search to the history.
            d_history.search(HistoryItem(word, ++search_id));
        }

        // Make the back button's drop-down menu reflect what
        // is in our history.
        QPopupMenu& backmenu = *d_backbutton_ptr->getMenu();
        const list<HistoryItem>& backoptions = d_history.getPreviousSearches();

        int k = 0;
        backmenu.clear();
        for(list<HistoryItem>::const_iterator i = backoptions.begin();
            (k < 9) && (i != backoptions.end()); ++i, ++k)
        {
            backmenu.insertItem(
                i->getText(), this, SLOT(_backMenu(int)), 0, i->getId()
            );
        }

        d_backbutton_ptr->update();


        // Make the forward button's drop-down menu reflect what
        // is in our history.
        QPopupMenu& nextmenu = *d_forwardbutton_ptr->getMenu();
        const list<HistoryItem>& nextoptions = d_history.getFutureSearches();

        list<HistoryItem>::const_iterator i;

        nextmenu.clear();
        for(k = 0, i = nextoptions.begin(); (k < 9) && (i != nextoptions.end());
            ++i, ++k)
        {
            nextmenu.insertItem(
                i->getText(), this, SLOT(_forwardMenu(int)), 0, i->getId()
            );
        }

        d_forwardbutton_ptr->update();


        // Make the dropdown list reflect what's in our history.
        d_searchbar_ptr->clear();
        const list<HistoryItem>& recent = d_history.getRecentSearches();
        for(i = recent.begin(); i != recent.end(); ++i)
        {
            d_searchbar_ptr->insertItem( i->getText() );
        }


        // Finally set the current contents of our search to be the
        // current word.
        d_searchbar_ptr->setEditText(word);
    }
}
