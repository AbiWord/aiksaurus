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
#include "ev_Menu_Actions.h"
#include "ap_Menu_Id.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
//#include "av_View.h"
#include "ev_EditMethod.h"

#include <iostream>
using namespace std;

bool AiksaurusABI_callback(AV_View*, EV_EditMethodCallData*);
void AiksaurusABI_addToMenus();
void AiksaurusABI_invoke();


const char* AiksaurusABI_MenuLabel = "&Thesaurus";
const char* AiksaurusABI_MenuTooltip = "Opens the thesaurus and finds synonyms.";

// -----------------------------------------------------------------------
//
//      Abiword Plugin Code
//
// -----------------------------------------------------------------------

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

    AiksaurusABI_addToMenus();
    
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




// AiksaurusABI_callback
// ---------------------
//   Callback function that will be called when we need to activate the 
//   thesaurus dialog.
//    
bool AiksaurusABI_callback(AV_View* v, EV_EditMethodCallData* d)
{
    AiksaurusABI_invoke();
    return true;
}



// AiksaurusABI_addToMenus
// -----------------------
//   Adds "Thesaurus" option to AbiWord's Tools Menu.
//
void
AiksaurusABI_addToMenus()
{
    XAP_App *pApp = XAP_App::getApp();

    EV_Menu_ActionSet* pActionSet = pApp->getMenuActionSet();
   
    EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
    
    pEMC->addEditMethod(new EV_EditMethod(
        "AiksaurusABI_callback",
        AiksaurusABI_callback,
        0,
        ""
    ));
        
    
    int frameCount = pApp->getFrameCount();
    for(int i = 0;i < frameCount;++i)
    {
        XAP_Frame* pFrame = pApp->getFrame(i);
        EV_Menu* pMenu = pFrame->getMainMenu();
        
        EV_Menu_Layout* pLayout = const_cast<EV_Menu_Layout*>(pMenu->getMenuLayout());
        
        XAP_Menu_Id id = pLayout->addLayoutItem(1, EV_MLF_Normal);
        
        EV_Menu_LabelSet* pLabelSet = const_cast<EV_Menu_LabelSet*>(pMenu->getMenuLabelSet());
        pLabelSet->addLabel(
                new EV_Menu_Label(
                    id, 
                    AiksaurusABI_MenuLabel,
                    AiksaurusABI_MenuTooltip
                )
        );
        
        pActionSet->addAction(new EV_Menu_Action(
            id,
            0, // no, don't have a sub menu.
            1, // yes, raises a dialog.
            0, // no, don't have a checkbox.
            "AiksaurusABI_callback",
            NULL,
            NULL        
        ));
    }
}




// -----------------------------------------------------------------------
//
//     Aiksaurus Invocation Code
//
// -----------------------------------------------------------------------


//
// AiksaurusABI_ucsToAscii
// -----------------------
//   Helper function to convert UCS-2 strings into Ascii.
//   NOTE: you must call delete[] on the returned test!!!
//
//   The thesaurus operates in pure ascii, and abiword documents operate
//   in UCS-2, so we need to be able to convert UCS-2 to Ascii in order
//   to tell what word the user has selected when they invoke the thesaurus.
//
inline static char*
AiksaurusABI_ucsToAscii(const UT_UCSChar* text)
{
    // calculate length of text so that we can create a character
    // buffer of equal size.
        const unsigned int length = UT_UCS_strlen(text);
        
    // allocate ascii characters plus room for a null terminator.    
        char* ret = new char[length+1];
        
    // do the string conversion.  this is simple we just cast to 
    // char since UCS-2 is the same as Ascii for english.    
        for(unsigned int i = 0;i < length;++i)
        {
            ret[i] = (char)text[i];
        }
        
    // finally null terminate the string.    
        ret[length] = '\0';

    // and now return it.
        return ret;    
}



//
// AiksaurusABI_asciiToUcs
// -----------------------
//   Helper function to convert Ascii strings into UCS-2.
//   NOTE: you must call delete[] on the returned text!!!
//
//   The thesaurus returns the replacement word in pure Ascii, but Abiword
//   documents operate in UCS-2. So, we have to convert to ascii to UCS-2
//   in order to be able to replace the user's word with their replacement
//   word.
//
inline static UT_UCSChar* 
AiksaurusABI_asciiToUcs(const char* text, int& length)
{
    // calculate the length of our text so we can create a UCS-2
    // buffer of equal size.
        length = strlen(text);
    
    // allocate UCS-2 character buffer of same size, plus room for 
    // a null terminator.    
        UT_UCSChar* ret = new UT_UCSChar[length+1];
    
    // convert ascii to UCS-2.  This is simply a cast-loop really.
        for(int i = 0;i < length;++i)
        {
            ret[i] = (UT_UCSChar)text[i];
        }
    
    // remember to null terminate the string.
        ret[length] = 0;

    // now return the string.
        return ret;
}



//
// AiksaurusABI_invoke
// -------------------
//   This is the function that we actually call to invoke the thesaurus.
//   It should be called when the user hits the thesaurus key (shift+f7?)
//   or chooses "thesaurus" from a menu.
//
void AiksaurusABI_invoke()
{
    // Get the current view that the user is in.
        XAP_Frame *pFrame = XAP_App::getApp()->getLastFocussedFrame();
        FV_View* pView = static_cast<FV_View*>(pFrame->getCurrentView());

    // If the user is on a word, but does not have it selected, we need
    // to go ahead and select that word so that the search/replace goes
    // correctly.
        pView->moveInsPtTo(FV_DOCPOS_BOW);
        pView->extSelTo(FV_DOCPOS_EOW_SELECT);    
 
    // Now we will figure out what word to look up when we open our dialog.
        char* search = NULL;
        if (!pView->isSelectionEmpty())
        {
            // We need to get the Ascii version of the current word.
            search = AiksaurusABI_ucsToAscii(
                    pView->getSelectionText()
            );
        }
    
    // Now we will run the thesaurus dialog and get a response.
    // We will automatically do a search for the selected/current word. 
        const char* response = AiksaurusGTK_doSearch(search);
    
        
    // Now that we have our replacement, we need to convert it to UCS-2. 
        int length;
        UT_UCSChar* replacement = AiksaurusABI_asciiToUcs(response, length);
    
        
    // Now, if our replacement has length, we can go ahead and run the 
    // replacement.  If the replacement has no length, we will do nothing.
        if (length)
        { 
            pView->cmdCharInsert(replacement, length);
        }    
    
    // Finally, we need to remember to delete search and replacement strings.
    // Note that "search" might be null so we only want to delete[] it if it
    // was actually initialized above. 
        if (search) 
            delete[] search;
    
        delete[] replacement;
}
