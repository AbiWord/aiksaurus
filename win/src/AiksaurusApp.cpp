/*
 * AiksaurusApp - A Win32 interface to the AikSaurus library
 * Copyright (C) 2001 by Jared Davis, Michael D. Pritchett
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

#include <windows.h>
#include <commctrl.h>   // includes the common control header
#include "AiksaurusApp.h"
#include "AiksaurusDlg.h"
#include "resource.h"


AiksaurusApp::AiksaurusApp()
{
	m_hInstance = NULL;
}

AiksaurusApp::~AiksaurusApp()
{
}

typedef BOOL __declspec(dllimport) (CALLBACK *InitCommonControlsEx_fn)(LPINITCOMMONCONTROLSEX lpInitCtrls);

void AiksaurusApp::initialize()
{

	// Ensure that common control DLL is loaded
	HINSTANCE hinstCC = LoadLibrary("comctl32.dll");
	InitCommonControlsEx_fn  pInitCommonControlsEx = NULL;
	if( hinstCC != NULL )
		pInitCommonControlsEx = (InitCommonControlsEx_fn)GetProcAddress( hinstCC, "InitCommonControlsEx" );
	if( pInitCommonControlsEx != NULL )
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_COOL_CLASSES | ICC_BAR_CLASSES 	// load the rebar and toolbar
					| ICC_TAB_CLASSES | ICC_UPDOWN_CLASS	// and tab and spin controls
					;
		pInitCommonControlsEx(&icex);
	}

	AiksaurusDlg dlg;

	// If something on Command Line
	if( !lookup.empty() )
	{

		dlg.setSearch( lookup );
	}
	// Check clipboard
	else
	{
        if( IsClipboardFormatAvailable(CF_TEXT) && OpenClipboard(NULL) ) 
		{
			HGLOBAL hMem = GetClipboardData(CF_TEXT); 
			if( hMem )
			{
				lookup = (char *) hMem;
				dlg.setSearch( lookup );
			}
		}
	}
	dlg.runModal( this );
	replace = dlg.getReplacement();
}

void AiksaurusApp::setLookup( char * word )
{
	lookup = word;
}


int WINAPI WinMain ( HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance,
                     PSTR szCmdLine, 
					 int iCmdShow)
{
	AiksaurusApp theApp;
	theApp.setInstance( hInstance );
	if( szCmdLine )
		theApp.setLookup( szCmdLine );
	theApp.initialize();

	return 0;
}
