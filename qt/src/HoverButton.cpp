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

#include "HoverButton.h"

namespace AiksaurusQT_impl
{
    //
    // HoverButton::_destruct()
    //   Basically do the destructor stuff.
    //   Free up any memory we've managed to allocate.
    //
    void HoverButton::_destruct()
    {
        delete d_hover_ptr;
        delete d_normal_ptr;
    }

    //
    // HoverButton::HoverButton()
    //   Create a hover button with a parent, hover and normal
    //   images.
    //
    HoverButton::HoverButton
    (QWidget* parent, const QPixmap& hover, const QPixmap& normal)
        : QPushButton(parent),
          d_lit(false),
          d_hover_ptr(0),
          d_normal_ptr(0)
    {
        try
        {
            d_hover_ptr = new QPixmap(hover);
            d_normal_ptr = new QPixmap(normal);
            setMouseTracking(true);
            setPixmap(*d_normal_ptr);
            setFlat(true);
        }

        catch(...)
        {
            _destruct();
            throw;
        }
    }


    //
    // HoverButton::~HoverButton()
    //   Destroy the button with the usual _destruct() call.
    //
    HoverButton::~HoverButton()
    {
        _destruct();
    }


    //
    // mouseMoveEvent
    //   Follow the mouse around and light up when it's
    //   over us.
    //
    void HoverButton::mouseMoveEvent(QMouseEvent* e)
    {
        bool lightup = (e->x() > 0) && (e->y() > 0) &&
                    (e->x() < width()) && (e->y() < height());

        if (lightup != d_lit)
        {
            setPixmap((lightup) ? (*d_hover_ptr) : (*d_normal_ptr));
            setFlat(!lightup);
        }

        d_lit = lightup;
    }
}

