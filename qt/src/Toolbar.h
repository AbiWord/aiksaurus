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

#ifndef INCLUDED_AIKSAURUS_QT_TOOLBAR_H
#define INCLUDED_AIKSAURUS_QT_TOOLBAR_H

#ifndef INCLUDED_AIKSAURUS_QT_HISTORY_H
    #include "History.h"
#endif

#ifndef QWIDGET_H
    #include <qwidget.h>
#endif

// Forward declarations
class QLabel;
class QHBoxLayout;
class QComboBox;

namespace AiksaurusQT_impl
{
    class MenuButton;
    class HoverButton;
    class DialogMediator;

    class HistoryItem
    {
        private:

            QString d_text;
            int d_id;

        public:

            HistoryItem() : d_text(""), d_id(0) {}
            HistoryItem(const QString& text, int id) : d_text(text), d_id(id) {}

            bool operator==(const HistoryItem& rhs) const
            { return getText() == rhs.getText(); }

            const QString& getText() const
            { return d_text; }

            int getId() const
            { return d_id; }
    };

    class Toolbar : public QWidget
    {
        Q_OBJECT

        private:
            Toolbar(const Toolbar& rhs);
            Toolbar& operator=(const Toolbar& rhs);

            void _destruct();

            History< HistoryItem > d_history;
            bool d_ishistorymove;

            QHBoxLayout* d_layout_ptr;
            MenuButton*  d_backbutton_ptr;
            MenuButton*  d_forwardbutton_ptr;
            QLabel*      d_searchfor_ptr;
            QComboBox*   d_searchbar_ptr;
            HoverButton* d_searchbutton_ptr;

        private slots:
            void _searchClicked();
            void _backClicked();
            void _forwardClicked();
            void _backMenu(int id);
            void _forwardMenu(int id);

        signals:
            void newSearch(const char* word);

        public:
            Toolbar(QWidget* parent);
            virtual ~Toolbar();

            void doSearch(const char* word);
    };
}

#endif // INCLUDED_AIKSAURUS_QT_TOOLBAR_H
