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

#import <objc/objc-runtime.h>
#import <AppKit/NSNibLoading.h>

#import "AiksaurusCocoa.h"

@implementation AiksaurusCocoaPanel

- (id)init
{
	NSBundle * bundle = nil;

	NSSize size;

	NSDictionary * dictionary = nil;

	[super initWithWindow:nil];

	m_aiksaurus = [[AiksaurusCocoa alloc] init];

	m_target = nil;

	bundle = [NSBundle bundleForClass:[self class]];

	dictionary = [NSDictionary dictionaryWithObject:self forKey:@"NSOwner"];

	if ([bundle loadNibFile:@"Panel" externalNameTable:dictionary withZone:[bundle zone]])
		{
			[oPanel setBecomesKeyOnlyIfNeeded:YES];

			if (m_aiksaurus)
				{
					if ([m_aiksaurus okay])
						{
							[oStatus setTextColor:[NSColor blackColor]];
							[oStatus setStringValue:@"Yay! Give me a word, please..."];

							[oResultsTable setDataSource:m_aiksaurus];
							[oResultsTable setDelegate:m_aiksaurus];
						}
					else
						{
							[oStatus setTextColor:[NSColor redColor]];
							[oStatus setStringValue:[m_aiksaurus lastError]];
						}
					[self sync];
				}
			else
				{
					[oStatus setTextColor:[NSColor redColor]];
					[oStatus setStringValue:@"Error: Insufficient memory!"];
				}

			if ([oHistory numberOfItems])
				[oHistory removeAllItems];

			size.width  = 0;
			size.height = 1;

			[oResultsTable setIntercellSpacing:size];
			[oResultsTable setDoubleAction:@selector(aDoubleClick:)];
		}
	return self;
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

- (void)lookupWord:(NSString *)word
{
	[oSearchField setStringValue:word];

	[self aSearchField:self];
}

- (void)sync
{
	if (m_aiksaurus == nil)
		return;

	if ([m_aiksaurus historyCanGoBack])
		[oBack    setEnabled:YES];
	else
		[oBack    setEnabled:NO];

	if ([m_aiksaurus historyCanGoForward])
		[oForward setEnabled:YES];
	else
		[oForward setEnabled:NO];

	if ([m_aiksaurus word])
		[oHistory setEnabled:YES];
	else
		[oHistory setEnabled:NO];

	[oResultsTable reloadData];
}

- (IBAction)aBack:(id)sender
{
	if ([m_aiksaurus historyBack])
		{
			[oHistory selectItemWithTitle:[m_aiksaurus word]];
			[self sync];
		}
}

- (IBAction)aForward:(id)sender
{
	if ([m_aiksaurus historyForward])
		{
			[oHistory selectItemWithTitle:[m_aiksaurus word]];
			[self sync];
		}
}

- (IBAction)aHistory:(id)sender
{
	NSString * old_word = [m_aiksaurus word];
	NSString * new_word = [oHistory titleOfSelectedItem];

	if (old_word == nil)
		{
			if ([new_word length])
				{
					[m_aiksaurus lookupWord:new_word reorderHistory:NO];
					[self sync];
				}
		}
	else if ([new_word length])
		{
			if ([new_word isEqualToString:old_word] == NO)
				{
					[m_aiksaurus lookupWord:new_word reorderHistory:NO];
					[self sync];
				}
		}
}

- (IBAction)aDoubleClick:(id)sender
{
	NSString * value = [m_aiksaurus clickColumn:[oResultsTable clickedColumn] atRow:[oResultsTable clickedRow]];

	if (value)
		{
			[oSearchField setStringValue:value];
			[self aSearchField:sender];
		}
}

- (IBAction)aResultsTable:(id)sender
{
	NSString * value = [m_aiksaurus clickColumn:[oResultsTable clickedColumn] atRow:[oResultsTable clickedRow]];

	if (value)
		{
			[oSearchField setStringValue:value];
			[oResultsTable reloadData];
		}
	[oStatus setStringValue:@""];
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
			if ([m_aiksaurus lookupWord:word reorderHistory:YES])
				{
					[oHistory insertItemWithTitle:word atIndex:0];
					[oHistory selectItemAtIndex:0];
					[self sync];
					[oStatus setTextColor:[NSColor blackColor]];
					[oStatus setStringValue:@"Next please..."];
				}
			else if ([m_aiksaurus okay])
				{
					[self sync];
					[oStatus setTextColor:[NSColor blueColor]];
					[oStatus setStringValue:@"No synonyms known. Nearby words:"];
				}
			else
				{
					[oStatus setTextColor:[NSColor redColor]];
					[oStatus setStringValue:[m_aiksaurus lastError]];
				}
		}
}

- (IBAction)aInsert:(id)sender
{
	if (m_target)
		objc_msgSend (m_target, m_action, [oSearchField stringValue]);
}

/* and, where target's action method has the form @selector(insertWord:), i.e.
   - (void)insertWord:(NSString *)word;
 */
- (void)setTargetForInsert:(id)target withAction:(SEL)action
{
	m_target = target;
	m_action = action;

	if (m_target)
		[oInsert setEnabled:YES];
	else
		[oInsert setEnabled:NO];
}

@end
