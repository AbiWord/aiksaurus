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

#include "MenuButton.h"

#ifndef QLAYOUT_H
    #include <qlayout.h>
#endif

#ifndef QPUSHBUTTON_H
    #include <qpushbutton.h>
#endif

#ifndef QPOPUPMENU_H
    #include <qpopupmenu.h>
#endif

#ifndef QPIXMAP_H
    #include <qpixmap.h>
#endif

#ifndef QCURSOR_H
    #include <qcursor.h>
#endif

namespace AiksaurusQT_impl
{
    // Picture for the down-arrow bitmap.
    static const char *downArrow[] =
    {
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
        "..........."
    };


    //
    // MenuButton::_destruct()
    //   Basically our destructor, useful for exception safety.
    //
    void MenuButton::_destruct()
    {
        delete d_layout_ptr;
        delete d_mainbutton_ptr;
        delete d_downarrow_ptr;
        delete d_hover_ptr;
        delete d_normal_ptr;
        delete d_menu_ptr;
    }


    //
    // MenuButton::MenuButton
    //   Construct a MenuButton with parent widget, hover and normal icons.
    //
    MenuButton::MenuButton
    (QWidget* parent, const QPixmap& hover, const QPixmap& normal)
    : QWidget(parent), d_lit(false)
    {
        try
        {
            d_layout_ptr = 0;
            d_mainbutton_ptr = 0;
            d_downarrow_ptr = 0;
            d_hover_ptr = 0;
            d_normal_ptr = 0;
            d_menu_ptr = 0;

            d_layout_ptr = new QHBoxLayout(this);
            d_mainbutton_ptr = new QPushButton(this);
            d_downarrow_ptr = new QPushButton(this);
            d_hover_ptr = new QPixmap(hover);
            d_normal_ptr = new QPixmap(normal);
            d_menu_ptr = new QPopupMenu(this);

            d_mainbutton_ptr->setPixmap(*d_normal_ptr);
            d_downarrow_ptr->setPixmap(downArrow);
            d_downarrow_ptr->setFlat(true);
            d_mainbutton_ptr->setFlat(true);

            d_layout_ptr->addWidget(d_mainbutton_ptr);
            d_layout_ptr->addWidget(d_downarrow_ptr);

            connect(d_downarrow_ptr, SIGNAL(clicked()),
                    this, SLOT(_downArrowClicked()));

            connect(d_menu_ptr, SIGNAL(aboutToHide()),
                    this, SLOT(_popupClosing()));

            setMouseTracking(true);

            update();
        }

        catch(...)
        {
            _destruct();
            throw;
        }
    }


    //
    // MenuButton::~MenuButton()
    //   All we need to do is destruct the object normally
    //
    MenuButton::~MenuButton()
    {
        _destruct();
    }


    //
    // MenuButton::getMenu()
    //   Return the popup menu so that the user can add/remove
    //   items from it.
    //
    QPopupMenu* MenuButton::getMenu()
    {
        return d_menu_ptr;
    }


    //
    // MenuButton::getButton()
    //   Return the button so that the user can connect to its signals.
    //
    QPushButton* MenuButton::getButton()
    {
        return d_mainbutton_ptr;
    }


    //
    // MenuButton::update()
    //   Called when menus are changed.  Update enabled-status to reflect
    //   if there are any items in the dropdown menu.
    //
    void MenuButton::update()
    {
        // Menu changed - update enabled status.
        d_enabled = d_menu_ptr->count();
        d_mainbutton_ptr->setEnabled(d_enabled);
        d_downarrow_ptr->setEnabled(d_enabled);
    }


    //
    // MenuButton::_updateHighlight()
    //   Determine if we should be lit up, then light up or
    //   dim ourself if we need to change states.
    //
    void MenuButton::_updateHighlight(int mouse_x, int mouse_y)
    {
        // Should we be lit up?
        bool lightup = (mouse_x > 0) && (mouse_y > 0) &&
                       (mouse_x < width()) && (mouse_y < height()) &&
                       (d_enabled);

        // Make sure we're how we ought to be.
        if (d_lit != lightup)
        {
            d_mainbutton_ptr->setPixmap((lightup) ? (*d_hover_ptr) : (*d_normal_ptr));
            d_mainbutton_ptr->setFlat(!lightup);
            d_downarrow_ptr->setFlat(!lightup);
        }

        // Note how we now are.
        d_lit = lightup;
    }


    //
    // MenuButton::mouseMoveEvent()
    //   When the mouse moves, make sure that our light-up status
    //   reflects how we want to be.
    //
    void MenuButton::mouseMoveEvent(QMouseEvent* e)
    {
        _updateHighlight(e->x(), e->y());
    }


    //
    // MenuButton::_downArrowClicked()
    //   Pop up the menu because they've clicked on the down arrow.
    //
    void MenuButton::_downArrowClicked()
    {
        // figure out where to pop up.
        QPoint location(0, d_mainbutton_ptr->height());

        // actually pop up the menu
        d_menu_ptr->popup(mapToGlobal(location));
    }


    //
    // MenuButton::_popupClosing()
    //   Update our highlight because the menu just closed,
    //   so we might not be over the button anymore.
    //
    void MenuButton::_popupClosing()
    {
        // first compute cursor's location relative to ourselves.
        QPoint me(mapToGlobal(QPoint(0, 0)));
        QPoint relative(QCursor::pos() - me);

        // Make sure that highlight follows cursor.
        _updateHighlight(relative.x(), relative.y());
    }
}

