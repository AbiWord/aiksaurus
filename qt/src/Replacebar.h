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

#ifndef INCLUDED_AIKSAURUS_QT_REPLACEBAR_H
#define INCLUDED_AIKSAURUS_QT_REPLACEBAR_H

#ifndef QWIDGET_H
    #include <qwidget.h>
#endif

// Forward declarations
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

namespace AiksaurusQT_impl
{
    class Replacebar : public QWidget
    {
        Q_OBJECT

        private:
            Replacebar(const Replacebar& rhs);
            Replacebar& operator=(const Replacebar& rhs);

            QHBoxLayout* d_layout_ptr;
            QLabel*      d_replacewith_ptr;
            QLineEdit*   d_replacement_ptr;
            QPushButton* d_replacebutton_ptr;
            QPushButton* d_cancelbutton_ptr;

            void _destruct();


        private slots:
            void _replaceClicked();
            void _cancelClicked();


        signals:
            void replace(const char* word);
            void cancel();


        public:
            Replacebar(QWidget* parent);
            virtual ~Replacebar();

            const char* getText() const;
            void setText(const char* text);
    };
}

#endif // INCLUDE_AIKSAURUS_QT_REPLACEBAR_H
