/*
 * Kaiksaur - A KDE interface to AikSaurus
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
 *
 */

#ifndef INCLUDED_JARED_GPL_QAIKSAURUS_HISTORY_H
#define INCLUDED_JARED_GPL_QAIKSAURUS_HISTORY_H

#include <vector>
#include <qstring.h>

class AikSaurusHistory
{
	private:
		
		std::vector<QString> d_history;
		int d_current;
		int d_end;
	
	public:

		AikSaurusHistory();

		void search(const QString& str);

		bool atEnd() const;
		bool atBegin() const;

		const QString& back();
		const QString& forward();
};

#endif // INCLUDED_JARED_GPL_QAIKSAURUS_HISTORY_H
