/*
 * AikSaurus - An open source thesaurus library
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

#ifndef INCLUDED_GPL_JARED_STRINGLOOPQUEUE_H
#define INCLUDED_GPL_JARED_STRINGLOOPQUEUE_H

/*
 * StringLoopQueue Data Structure
 *
 * This acts as if it were a regular circular queue, with a
 * slight change: if the queue is full, it overwrites the 
 * oldest elements.  
 * 
 * The structure is useful for implementing the "nearby words" 
 * feature of the thesaurus.
 * 
 */

#include <string>

class StringLoopQueue
{
	private:

		std::string* d_array;
		const int d_size;
		int d_rear;
		int d_count;
		
		StringLoopQueue(const StringLoopQueue& rhs);
		const StringLoopQueue& operator=(const StringLoopQueue& rhs);
		
	public:

		StringLoopQueue(int size)
		: d_array(NULL), d_size(size), d_rear(0), d_count(0)
		{
			assert(d_size > 0);	
			d_array = new string[size];
		}
		
		~StringLoopQueue()
		{
			if (d_array)
			{
				delete[] d_array;
			}
		}
		
		int size() const
		{
			return d_size;
		}
		
		bool empty()
		{
			return (d_count == 0);
		}

		bool full()
		{
			return (d_count == size());
		}

		void push(const string& x)
		{
			d_array[d_rear] = x;
			
			d_rear = (d_rear + 1) % size();
			
			if (!full()) 
			{
				d_count++;
			}
		}
		
		string pop()
		{
			if (empty())
			{
				return "";
			}

			int ret = d_rear - d_count;
			if (ret < 0)
			{	
				ret += size();
			}

			d_count--;

			return d_array[ret];
		}


		void debug()
		{
			cout << "StringLoopQueue Debug: " << endl;
			cout << "  Size: " << size() << endl;
			cout << "  Empty: " << empty() << endl;
			cout << "  Full: " << full() << endl;
			cout << "  Rear: " << d_rear << endl;
			cout << "  Count: " << d_count << endl;
			cout << "  Array: " << endl;

			for(int i = 0;i < size();++i)
			{
				cout << "     Array[" << i << "] = " << d_array[i] << endl;
			}
		}
};





#endif // INCLUDED_GPL_JARED_STRINGLOOPQUEUE_H
