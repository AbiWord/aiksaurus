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

#ifndef INCLUDED_AIKSAURUS_QT_HISTORY_H
#define INCLUDED_AIKSAURUS_QT_HISTORY_H

#include <list>
#include <cassert>

namespace AiksaurusQT_impl
{
    template<class T>
    class History
    {
        private:
            History(const History<T>& rhs);
            History& operator=(const History<T>& rhs);

            T d_current;
            std::list<T> d_previous;
            std::list<T> d_future;
            std::list<T> d_recent;

        public:
            History() {}
            ~History() {}

            const T& getCurrent() const { return d_current; }
            const std::list<T>& getPreviousSearches() const { return d_previous; }
            const std::list<T>& getFutureSearches() const { return d_future; }
            const std::list<T>& getRecentSearches() const { return d_recent; }

            void search(const T& newsearch);
            void moveBack();
            void moveForward();
    };

    template<class T>
    void History<T>::search(const T& newsearch)
    {
        if (d_current != T())
            d_previous.push_front(d_current);

        d_current = newsearch;
        d_future.clear();
        d_recent.remove(d_current);
        d_recent.push_front(d_current);

        if (d_recent.size() > 9)    // limit recent list to 9 entries.
            d_recent.pop_back();
    }

    template<class T>
    void History<T>::moveBack()
    {
        assert(!d_previous.empty());
        d_future.push_front(d_current);
        d_current = *(d_previous.begin());
        d_previous.pop_front();
    }

    template<class T>
    void History<T>::moveForward()
    {
        assert(!d_future.empty());
        d_previous.push_front(d_current);
        d_current = *(d_future.begin());
        d_future.pop_front();
    }
}

#endif // INCLUDED_AIKSAURUS_QT_HISTORY_H
