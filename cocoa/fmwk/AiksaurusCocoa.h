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

#import <Cocoa/Cocoa.h>

@interface AiksaurusCocoaMeaning : NSObject
{
	BOOL		m_titles;

	NSString *	m_title_1;
	NSString *	m_title_2;

	NSMutableArray *	m_synonyms;

	int			m_rows;
}
- (id)initWithoutTitles;
- (id)initWithTitle:(NSString *)title withAlternativeTitle:(NSString *)alt;
- (void)dealloc;

- (void)synonymAdd:(NSString *)synonym;
- (NSString *)synonymAtPosition:(unsigned)position;
- (unsigned)synonyms;

- (NSString *)clickColumn:(int)column atRow:(int)row;

- (int)numberOfRowsInTableView;
- (NSString *)objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;
@end

@interface AiksaurusCocoa : NSObject
{
	void *	m_aiksaurus;

	unsigned	m_length;
	int			m_position;

	NSMutableArray *	m_history;
	NSMutableArray *	m_meanings;

	int			m_rows;
	int			m_highlight_row;
	int			m_highlight_col;
}
- (id)init;
- (void)dealloc;

- (BOOL)okay;
- (NSString *)lastError;

- (BOOL)historyBack;
- (BOOL)historyForward;
- (BOOL)historyCanGoBack;
- (BOOL)historyCanGoForward;

- (void)setWord:(NSString *)word reorderHistory:(BOOL)reorder;
- (NSString *)word;

- (BOOL)lookupWord:(NSString *)word reorderHistory:(BOOL)reorder;

- (AiksaurusCocoaMeaning *)meaningAtPosition:(unsigned)position;
- (unsigned)meanings;

- (NSString *)clickColumn:(int)column atRow:(int)row;

/* NSTableDataSource informal protocol
 */
- (int)numberOfRowsInTableView:(NSTableView *)aTableView;
- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;

/* NSTableView delegate
 */
- (void)tableView:(NSTableView *)aTableView willDisplayCell:(id)aCell forTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;
- (BOOL)tableView:(NSTableView *)aTableView shouldSelectRow:(int)rowIndex;
@end
