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

#import "AiksaurusCocoaMain.h"

@implementation AiksaurusCocoaMain

- (void)awakeFromNib
{
	m_aiksaurus = [[AiksaurusCocoa alloc] init];

	if (m_aiksaurus)
		{
			if ([m_aiksaurus okay])
				{
					[oStatus setTextColor:[NSColor blackColor]];
					[oStatus setStringValue:@"Yay! Give me a word, please..."];
				}
			else
				{
					[oStatus setTextColor:[NSColor redColor]];
					[oStatus setStringValue:[m_aiksaurus lastError]];
				}
		}
	else
		{
			[oStatus setTextColor:[NSColor redColor]];
			[oStatus setStringValue:@"Error: Insufficient memory!"];
		}
	if ([oHistory numberOfItems])
		[oHistory removeAllItems];

	[self sync];
}

- (void)dealloc
{
	if (m_aiksaurus)
		{
			[m_aiksaurus dealloc];
			m_aiksaurus = nil;
		}
	[super dealloc];
}

- (void)sync
{
	int length   = [m_aiksaurus historyLength];
	int position = [m_aiksaurus historyPosition];

	if (length)
		{
			if (position == 0)
				[oBack    setEnabled:NO];
			else
				[oBack    setEnabled:YES];
			if (position == (length - 1))
				[oForward setEnabled:NO];
			else
				[oForward setEnabled:YES];
			[oHistory setEnabled:YES];
			[oHistory selectItemAtIndex:position];
		}
	else
		{
			[oBack    setEnabled:NO];
			[oForward setEnabled:NO];
			[oHistory setEnabled:NO];
		}
}

- (IBAction)aBack:(id)sender
{
	if ([m_aiksaurus historyBack])
		[self sync];
}

- (IBAction)aForward:(id)sender
{
	if ([m_aiksaurus historyForward])
		[self sync];
}

- (IBAction)aHistory:(id)sender
{
	int old_position = [m_aiksaurus historyPosition];
	int new_position = [oHistory indexOfSelectedItem];

	if (old_position != new_position)
		if ([m_aiksaurus setHistoryPosition:new_position])
			[self sync];
}

- (IBAction)aResultsTable:(id)sender
{
}

- (IBAction)aSearch:(id)sender
{
	[self aSearchField:sender];
}

- (IBAction)aSearchField:(id)sender
{
	NSString * word = [oSearchField stringValue];

	if (word)
		{
			if ([m_aiksaurus lookupWord:word])
				{
					[self sync];
					[oStatus setTextColor:[NSColor blackColor]];
					[oStatus setStringValue:@"Next please..."];
				}
			else if ([m_aiksaurus okay])
				{
					[oStatus setTextColor:[NSColor blueColor]];
					[oStatus setStringValue:@"Sorry! Try again..."];
				}
			else
				{
					[oStatus setTextColor:[NSColor redColor]];
					[oStatus setStringValue:[m_aiksaurus lastError]];
				}
		}
}

@end
