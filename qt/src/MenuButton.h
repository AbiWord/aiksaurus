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

#ifndef INCLUDED_AIKSAURUS_QT_MENUBUTTON_H
#define INCLUDED_AIKSAURUS_QT_MENUBUTTON_H

#ifndef QWIDGET_H
    #include <qwidget.h>
#endif

// Forward declarations
class QHBoxLayout;
class QPushButton;
class QPixmap;
class QMouseEvent;
class QPopupMenu;

namespace AiksaurusQT_impl
{
    class MenuButton : public QWidget
    {
        Q_OBJECT

        private:
        // member functions
            MenuButton(const MenuButton& rhs);
            MenuButton& operator=(const MenuButton& rhs);
            void _destruct();
            void _updateHighlight(int mouse_x, int mouse_y);

        // internal data members
            bool d_lit;
            bool d_enabled;

        // gui elements
            QHBoxLayout *d_layout_ptr;
            QPushButton *d_mainbutton_ptr;
            QPushButton *d_downarrow_ptr;
            QPixmap     *d_hover_ptr;
            QPixmap     *d_normal_ptr;
            QPopupMenu  *d_menu_ptr;

        private slots:
            void _downArrowClicked();
            void _popupClosing();

        protected:
            virtual void mouseMoveEvent(QMouseEvent* e);

        public:
        // creation and destruction
            MenuButton(QWidget* parent, const QPixmap& hover, const QPixmap& normal);
            virtual ~MenuButton();

        // modify menu or connect button signal.
            QPopupMenu* getMenu();
            QPushButton* getButton();

        // call update when menu is modified.
            void update();
    };
}

#endif // INCLUDED_AIKSAURUS_QT_MENUBUTTON_H
