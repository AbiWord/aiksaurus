/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* Aiksaurus / Cocoa front-end
 * Copyright (C) 2003 Francis James Franklin <fjf@alinameridon.com>
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
 */

#include "AiksaurusCocoa.h"
#include "Aiksaurus.h"

@implementation AiksaurusCocoa

- (id)init
{
	[super init];

	m_aiksaurus = 0;

	m_length   = 0;
	m_position = 0;

	NSBundle * bundle = [NSBundle bundleForClass:[self class]];

	NSString * path_meanings = [bundle pathForResource:@"meanings" ofType:@"dat"];
	NSString * path_words    = [bundle pathForResource:@"words"    ofType:@"dat"];

	if (path_meanings && path_words)
		{
			try
				{
					Aiksaurus * aik = new Aiksaurus([path_meanings UTF8String],
													[path_words    UTF8String]);
					m_aiksaurus = reinterpret_cast<void *>(aik);
				}
			catch (...)
				{
					m_aiksaurus = 0;
				}
		}
	return self;
}

- (void)dealloc
{
	if (m_aiksaurus)
		{
			Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);
			delete aik;
			m_aiksaurus = 0;
		}
	[super dealloc];
}

- (BOOL)okay
{
	if (!m_aiksaurus) return NO;

	Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);

	const char * aik_error = aik->error ();

	return (*aik_error ? NO : YES);
}

- (NSString *)lastError
{
	if (!m_aiksaurus) return @"Error: Couldn't create Aiksaurus library!";

	Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);

	const char * aik_error = aik->error ();

	return (*aik_error ? [NSString stringWithCString:aik_error] : nil);
}

- (int)historyLength
{
	return m_length;
}

- (int)historyPosition
{
	return m_position;
}

- (BOOL)setHistoryPosition:(int)position
{
	if ((position >= 0) && (position < m_length))
		{
			m_position = position;
			return YES;
		}
	return NO;
}

- (BOOL)historyBack
{
	if (m_position)
		{
			--m_position;
			return YES;
		}
	return NO;
}

- (BOOL)historyForward
{
	if (m_position + 1 < m_length)
		{
			++m_position;
			return YES;
		}
	return NO;
}

- (BOOL)lookupWord:(NSString *)word
{
	if (!m_aiksaurus || !word) return NO;

	Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);

	if (!aik->find ([word UTF8String])) return NO;

	int prev_meaning = -1;
	int this_meaning = -1;

	for (const char * r = aik->next (this_meaning); *r; r = aik->next (this_meaning))
		{
			if (prev_meaning != this_meaning)
				{
					NSString * title_1 = [NSString stringWithUTF8String:r];
					r = aik->next (this_meaning);
					NSString * title_2 = [NSString stringWithUTF8String:r];
					// TODO
				}
			else
				{
					NSString * synonym = [NSString stringWithUTF8String:r];
					// TODO
				}
		}
	return YES;
}

@end
