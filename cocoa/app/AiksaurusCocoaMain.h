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

#import "AiksaurusCocoa.h"

@interface AiksaurusCocoaMain : NSObject
{
	AiksaurusCocoa *	m_aiksaurus;

	IBOutlet NSButton *			oBack;
	IBOutlet NSButton *			oForward;
	IBOutlet NSPopUpButton *	oHistory;
	IBOutlet NSTableView *		oResultsTable;
	IBOutlet NSTextField *		oSearchField;
	IBOutlet NSTextField *		oStatus;
}
- (void)awakeFromNib;
- (void)dealloc;

- (void)pasteViaService:(NSPasteboard *)pboard userData:(NSString *)userData error:(NSString **)error;

- (void)sync;

- (IBAction)aBack:(id)sender;
- (IBAction)aForward:(id)sender;
- (IBAction)aHistory:(id)sender;
- (IBAction)aDoubleClick:(id)sender;
- (IBAction)aResultsTable:(id)sender;
- (IBAction)aSearch:(id)sender;
- (IBAction)aSearchField:(id)sender;
@end
