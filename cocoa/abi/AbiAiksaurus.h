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

#import "XAP_CocoaPlugin.h"

@class AiksaurusCocoaPanel;

@interface AbiAiksaurus : NSObject <XAP_CocoaPluginDelegate>
{
	AiksaurusCocoaPanel *	m_aiksaurus;

	XAP_CocoaPlugin *	m_AbiWord;

	id <NSObject, XAP_CocoaPlugin_MenuItem>		m_ContextMenuItem;
}
- (id)init;
- (void)dealloc;

- (void)invoke:(id)sender;
- (void)insertWord:(NSString *)word;

/**
 * This will be called immediately after initialization;
 * 
 * If the bundle's principal class implements *only* this method, it must immediately set
 * the real XAP_CocoaPluginDelegate object as AbiWord's delegate using XAP_CocoaPlugin's
 * setDelegate: method.
 * 
 * The plug-in should not activate - wait for XAP_CocoaPluginDelegate's pluginActivate:
 * method to be called.
 * 
 * \param AbiWord The main interface to AbiWord.
 * 
 * \return Should return NO if for some reason the plug-in won't work with the current
 *         version of AbiWord.
 */
- (BOOL)pluginCanRegisterForAbiWord:(XAP_CocoaPlugin *)AbiWord version:(NSString *)version interface:(unsigned long)interface;

/**
 * \return Should return YES if the plug-in is active; otherwise NO.
 */
- (BOOL)pluginIsActive;

/**
 * This is a request for the plug-in to activate.
 */
- (void)pluginActivate;   /* Add menuitems etc. */

/**
 * This is a request for the plug-in to deactivate. The plug-in *must* comply.
 */
- (void)pluginDeactivate; /* Remove them...     */

/**
 * The plug-in should attempt to save all files, etc., since it is about to be asked to
 * deactivate. Returning NO will not necessarily prevent the request to deactivate.
 * 
 * \return Should return NO *only* if the user has answered "Cancel" to an alert about
 *         an unsaved document; otherwise YES.
 */
- (BOOL)pluginCanDeactivate;

/**
 * AbiWord will call this if the focus changes to a different document, or different window
 * or panel, or if the current document is closed.
 */
- (void)pluginCurrentDocumentHasChanged;

/**
 * \return The name of the plug-in.
 */
- (NSString *)pluginName;

/**
 * \return The name(s) of the plug-in author(s).
 */
- (NSString *)pluginAuthor;

/**
 * \return The version of the plug-in.
 */
- (NSString *)pluginVersion;

/**
 * \return A short description of what the plug-in does.
 */
- (NSString *)pluginDescription;

/**
 * \return A short description of how to use the plug-in.
 */
- (NSString *)pluginUsage;

@end
