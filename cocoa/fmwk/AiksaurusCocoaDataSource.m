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

#import "AiksaurusCocoaDataSource.h"

@implementation AiksaurusCocoaDataSource

- (id)initWithAiksaurus:(AiksaurusCocoa *)aiksaurus
{
	[super init];

	m_aiksaurus = aiksaurus;

	return self;
}

- (void)dealloc
{
	[super dealloc];
}

- (int)numberOfRowsInTableView:(NSTableView *)aTableView
{
	return [m_aiksaurus numberOfRowsInTableView];
}

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
	AiksaurusCocoaMeaning * acm = nil;

	int rows = 0;
	int sub_rows = 0;

	unsigned meanings = [m_aiksaurus meanings];
	unsigned i;

	NSString * col = (NSString *) [aTableColumn identifier];

	int colIndex = 3;

	if ([col isEqualToString:@"1"])
		colIndex = 0;
	else if ([col isEqualToString:@"2"])
		colIndex = 1;
	else if ([col isEqualToString:@"3"])
		colIndex = 2;

	for (i = 0; i < meanings; i++)
		{
			acm = (AiksaurusCocoaMeaning *) [m_aiksaurus meaningAtPosition:i];
			sub_rows = [acm numberOfRowsInTableView];
			if ((rowIndex >= rows) && (rowIndex < rows + sub_rows))
				{
					/* */
					break;
				}
			rows += sub_rows;
		}
	return @"test";
}

@end
