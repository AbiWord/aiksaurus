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

#ifndef INCLUDED_AIKSAURUS_QT_HOVERBUTTON_H
#define INCLUDED_AIKSAURUS_QT_HOVERBUTTON_H

#ifndef QPUSHBUTTON_H
    #include <qpushbutton.h>
#endif

// Forward declarations
class QPixmap;

namespace AiksaurusQT_impl
{
    class HoverButton : public QPushButton
    {
        private:

            HoverButton(const HoverButton& rhs);
            HoverButton& operator=(const HoverButton& rhs);

            void _destruct();

            bool d_lit;

            QPixmap* d_hover_ptr;
            QPixmap* d_normal_ptr;

        protected:

            virtual void mouseMoveEvent(QMouseEvent* e);

        public:

            HoverButton(QWidget* parent, const QPixmap& hover, const QPixmap& normal);
            virtual ~HoverButton();

    };
}

#endif // INCLUDED_AIKSAURUS_QT_HOVERBUTTON_H
