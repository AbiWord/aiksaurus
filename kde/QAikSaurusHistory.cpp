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

#include "QAikSaurusHistory.h"

using namespace std;

AikSaurusHistory::AikSaurusHistory()
: d_history(10), d_current(-1), d_end(0)
{

}

bool AikSaurusHistory::atBegin() const
{
	return (d_current <= 0);
}

bool AikSaurusHistory::atEnd() const
{
	return (d_current == d_end - 1);
}

const QString& AikSaurusHistory::back()
{
	assert(!atBegin());
	--d_current;
	return(d_history[d_current]);
}

const QString& AikSaurusHistory::forward()
{
	assert(!atEnd());
	++d_current;
	return(d_history[d_current]);
}

void AikSaurusHistory::search(const QString& search)
{
	// new search has been entered.  current entry immediately
	// becomes the end of the list.
	d_end = d_current + 1;

	// now, we want to add our new search at the position of
	// d_end.  we need to make sure we aren't going to run into
	// size problems.
	if (static_cast<unsigned int>(d_end) == d_history.size())
	{
		d_history.push_back(search);
	}
	else
	{
		d_history[d_end] = search;
	}
	
	// now, we need to advance current to the next position, 
	// since what we just entered is now the current search.
	d_current++;

	// and, of course, we need to add one to d_end, since the
	// end is not one further than it was.
	d_end++;
}

