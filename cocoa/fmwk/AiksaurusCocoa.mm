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

@implementation AiksaurusCocoaMeaning

- (id)initWithTitle:(NSString *)title withAlternativeTitle:(NSString *)alt
{
	[super init];

	m_title_1 = title;
	m_title_2 = alt;

	[m_title_1 retain];
	[m_title_2 retain];

	m_synonyms = [NSMutableArray array];

	[m_synonyms retain];

	m_rows = 1;

	return self;
}

- (void)dealloc
{
	[m_title_1 release];
	[m_title_2 release];

	[m_synonyms release];

	[super dealloc];
}

- (void)synonymAdd:(NSString *)synonym
{
	[m_synonyms addObject:synonym];

	m_rows = 1 + ((int) [m_synonyms count] + 3) >> 2;
}

- (NSString *)synonymAtPosition:(unsigned)position
{
	if ((position >= 0) && (position < [m_synonyms count]))
		{
			return (NSString *) [m_synonyms objectAtIndex:position];
		}
	return nil;
}

- (unsigned)synonyms
{
	return [m_synonyms count];
}

- (int)numberOfRowsInTableView
{
	return m_rows;
}

- (NSString *)objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	NSString * value = @"";
	NSString * col = (NSString *) [aTableColumn identifier];

	int colIndex = 3;

	if ([col isEqualToString:@"1"])
		colIndex = 0;
	else if ([col isEqualToString:@"2"])
		colIndex = 1;
	else if ([col isEqualToString:@"3"])
		colIndex = 2;

	if (rowIndex)
		{
			int index = (rowIndex - 1) * 4 + colIndex;
			if (index < (int) [m_synonyms count])
				value = (NSString *) [m_synonyms objectAtIndex:index];
		}
	else if (colIndex == 0)
		{
			value = m_title_1;
		}
	else if (colIndex == 2)
		{
			value = m_title_2;
		}
	return value;
}

@end

@implementation AiksaurusCocoa

- (id)init
{
	[super init];

	m_aiksaurus = 0;

	m_length   = 0;
	m_position = 0;

	m_history  = [NSMutableArray array];
	m_meanings = [NSMutableArray array];

	[m_history  retain];
	[m_meanings retain];

	m_rows = 0;

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

	[m_history  release];
	[m_meanings release];

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

- (BOOL)historyBack
{
	BOOL change = [self historyCanGoBack];

	if (change)
		[self lookupWord:(NSString *)[m_history objectAtIndex:(m_position-1)] reorderHistory:NO];

	return change;
}

- (BOOL)historyForward
{
	BOOL change = [self historyCanGoForward];

	if (change)
		[self lookupWord:(NSString *)[m_history objectAtIndex:(m_position+1)] reorderHistory:NO];

	return change;
}

- (BOOL)historyCanGoBack
{
	return (m_position ? YES : NO);
}

- (BOOL)historyCanGoForward
{
	return ((m_position + 1 < (int) m_length) ? YES : NO);
}

- (void)setWord:(NSString *)newword reorderHistory:(BOOL)reorder
{
	if (newword == nil) return;
	if ([newword length] == 0) return;

	NSString * current = [self word];

	if (current == nil)
		{
			[m_history addObject:newword];

			m_length = [m_history count];
			m_position = 0;
		}
	else if ([current isEqualToString:newword] == NO)
		{
			unsigned position = m_length;

			for (unsigned i = 0; i < m_length; i++)
				{
					NSString * str = (NSString *) [m_history objectAtIndex:i];
					if ([newword isEqualToString:str])
						{
							position = i;
							break;
						}
				}
			if (position == m_length)
				{
					[m_history addObject:newword];
					m_length = [m_history count];
					m_position = m_length - 1;
				}
			else if (reorder && (position < m_length - 1))
				{
					[m_history removeObjectAtIndex:position];
					[m_history addObject:newword];
					m_length = [m_history count];
					m_position = m_length - 1;
				}
			else
				{
					m_position = position;
				}
		}
}

- (NSString *)word
{
	NSString * current = nil;

	if (m_length) current = (NSString *) [m_history objectAtIndex:m_position];

	return current;
}

- (BOOL)lookupWord:(NSString *)newword reorderHistory:(BOOL)reorder
{
	if (!m_aiksaurus || !newword)
		return NO;
	if ([newword length] == 0)
		return NO;

	NSString * current = [self word];
	if (current)
		if ([current isEqualToString:newword])
			return YES;

	Aiksaurus * aik = reinterpret_cast<Aiksaurus *>(m_aiksaurus);

	if (!aik->find ([newword UTF8String])) return NO; // TODO: close matches

	[self setWord:newword reorderHistory:reorder];

	[m_meanings removeAllObjects];

	int prev_meaning = -1;
	int this_meaning = -1;

	for (const char * r = aik->next (this_meaning); *r; r = aik->next (this_meaning))
		{
			if (prev_meaning != this_meaning)
				{
					NSString * title_1 = [NSString stringWithUTF8String:r];
					r = aik->next (this_meaning);
					NSString * title_2 = [NSString stringWithUTF8String:r];

					AiksaurusCocoaMeaning * acm = nil;
					acm = [[AiksaurusCocoaMeaning alloc] initWithTitle:title_1 withAlternativeTitle:title_2];

					[m_meanings addObject:acm];
					[acm release]; // ??

					prev_meaning = this_meaning;
				}
			else
				{
					AiksaurusCocoaMeaning * acm = (AiksaurusCocoaMeaning *) [m_meanings lastObject];
					if (acm) [acm synonymAdd:[NSString stringWithUTF8String:r]];
				}
		}

	/* calculate number of rows in standard table layout; cache for efficient use later
	 */
	m_rows = 0;

	int count = (int) [m_meanings count];

	for (int i = 0; i < count; i++)
		{
			AiksaurusCocoaMeaning * acm = (AiksaurusCocoaMeaning *) [m_meanings objectAtIndex:i];
			m_rows += [acm numberOfRowsInTableView];
		}

	return YES;
}

- (AiksaurusCocoaMeaning *)meaningAtPosition:(unsigned)position
{
	if ((position >= 0) && (position < [m_meanings count]))
		{
			return (AiksaurusCocoaMeaning *) [m_history objectAtIndex:position];
		}
	return nil;
}

- (unsigned)meanings
{
	return [m_meanings count];
}

- (int)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return m_rows;
}

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	NSString * value = @"";

	int rows = 0;

	unsigned count = [m_meanings count];

	for (unsigned i = 0; i < count; i++)
		{
			AiksaurusCocoaMeaning * acm = (AiksaurusCocoaMeaning *) [m_meanings objectAtIndex:i];
			int sub_rows = [acm numberOfRowsInTableView];
			if ((rowIndex >= rows) && (rowIndex < rows + sub_rows))
				{
					value = [acm objectValueForTableColumn:aTableColumn row:(rowIndex - rows)];
					break;
				}
			rows += sub_rows;
		}
	return value;
}

@end
