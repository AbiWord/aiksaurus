/* -*- mode: C++; tab-width: 4; c-basic-offset: 4; -*- */

/* Aiksaurus / Cocoa front-end / AbiWord Plug-in
 * Copyright (C) 2005 Francis James Franklin
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

#import "AbiAiksaurus.h"

@implementation AbiAiksaurus

- (id)init
{
	if (self = [super init])
		{
			m_aiksaurus = 0;
		}
	return self;
}

- (void)dealloc
{
	if (m_aiksaurus)
		{
			[m_aiksaurus close];
			[m_aiksaurus release];
			m_aiksaurus = 0;
		}
	[super dealloc];
}

- (void)invoke:(id)sender
{
	id <NSObject, XAP_CocoaPlugin_Document> doc = [m_AbiWord currentDocument]; /* may return nil */
	if (doc)
		{
			NSString * word = [doc selectWord];
			if (word)
				{
					if (!m_aiksaurus)
						{
							m_aiksaurus = [[AiksaurusCocoaPanel alloc] init];

							[m_aiksaurus setTargetForInsert:self withAction:@selector(insertWord:)];
						}
					[[m_aiksaurus window] orderFront:self];

					[m_aiksaurus lookupWord:word];
				}
		}
}

- (void)insertWord:(NSString *)word
{
	id <NSObject, XAP_CocoaPlugin_Document> doc = [m_AbiWord currentDocument]; /* may return nil */
	if (doc)
		{
			[doc insertText:word];
		}
}

- (BOOL)pluginCanRegisterForAbiWord:(XAP_CocoaPlugin *)AbiWord version:(NSString *)version interface:(unsigned long)interface
{
	m_AbiWord = AbiWord;

	return ((interface >= 20050303) ? YES : NO);
}

- (BOOL)pluginIsActive
{
	return (m_aiksaurus ? YES : NO);
}

- (void)pluginActivate
{
	if (!m_aiksaurus)
		{
			if (m_ContextMenuItem = [m_AbiWord contextMenuItemWithLabel:@"Thesaurus"])
				{
					[m_ContextMenuItem setAction:@selector(invoke:)];
					[m_ContextMenuItem setTarget:self];
					[m_ContextMenuItem retain];
				}
		}
}

- (void)pluginDeactivate
{
	if (m_aiksaurus)
		{
			if (m_ContextMenuItem)
				{
					[m_ContextMenuItem release];
					m_ContextMenuItem = 0;
				}
			if (m_aiksaurus)
				{
					[m_aiksaurus close];
					[m_aiksaurus release];
					m_aiksaurus = 0;
				}
		}
}

- (BOOL)pluginCanDeactivate
{
	return YES;
}

- (void)pluginCurrentDocumentHasChanged
{
	/* hmm... */
}

- (NSString *)pluginName
{
	return @"Aiksaurus";
}

- (NSString *)pluginAuthor;
{
	return @"Aiksaurus by Jared Davis; Cocoa port by Francis Franklin (fjf)";
}

- (NSString *)pluginVersion;
{
	return @"1.0";
}

- (NSString *)pluginDescription;
{
	return @"English-language thesaurus based on the Aiksaurus library: http://www.aiksaurus.com/";
}

- (NSString *)pluginUsage;
{
	return @"Use via the document's contextual menu.";
}

@end
