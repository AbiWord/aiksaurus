/*
 * AiksaurusABI - Abiword plugin for AikSaurus
 * Copyright (C) 2001 by Jared Davis
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

#include <AiksaurusGTK.h>
#include "xap_Module.h"
#include "xap_App.h"
#include "xap_Frame.h"
#include "fv_View.h"


ABI_FAR extern "C"
int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "Aiksaurus";
    mi->desc = "English-language thesaurus based on the Aiksaurus library: "
               "http://zeddiclan.com/aiksaurus/";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Jared Davis (jared@zeddiclan.com)";
    mi->usage = "No Usage";
    
    AiksaurusGTK_setTitle("AbiWord Thesaurus");

    XAP_Frame *pFrame = XAP_App::getApp()->getLastFocussedFrame();
    FV_View* pView = static_cast<FV_View*>(pFrame->getCurrentView());
    pView->moveInsPtTo(FV_DOCPOS_BOW);
    pView->extSelTo(FV_DOCPOS_EOW_SELECT);    
  
    char* search = NULL;
    if ( !pView->isSelectionEmpty() )
    {
        // selection is not empty.
        UT_UCSChar *text= pView->getSelectionText();
        
        // convert string to ascii from ucs-2.
        int length = UT_UCS_strlen(text);
        search = new char[length+1];
        for(int i = 0;i < length;++i)
        {
            search[i] = (char)text[i];
        }
        search[length] = '\0';
    }
    
    // run thesaurus dialog.
    const char* change = AiksaurusGTK_doSearch(search);
    if (search) 
        delete[] search;
    
    // convert replacement from ascii to ucs-2.
    int length = strlen(change);
    UT_UCSChar* replacement = new UT_UCSChar[length+1];
    for(int i = 0;i < length;++i)
    {
        replacement[i] = (UT_UCSChar)change[i];
    }
    replacement[length] = 0;
               
    if (length)
    { 
        pView->cmdCharInsert(replacement, length);
    }    
    delete[] replacement;
        
    return 1;
}

ABI_FAR extern "C"
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;
    return 1;
}

ABI_FAR extern "C"
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
    return 1; 
}
