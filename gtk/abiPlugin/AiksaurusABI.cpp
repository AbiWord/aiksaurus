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
#include "ap_Menu_Id.h"
#include "ev_Menu_Actions.h"
#include "ev_Menu.h"
#include "ev_Menu_Layouts.h"
#include "ev_Menu_Labels.h"
#include "ev_EditMethod.h"

#include <iostream>
using namespace std;

bool AiksaurusABI_invoke(AV_View* v, EV_EditMethodCallData *d);

static const char* AiksaurusABI_MenuLabel = "&Thesaurus";
static const char* AiksaurusABI_MenuTooltip = "Opens the thesaurus and finds synonyms.";


//
// AiksaurusABI_addToMenus
// -----------------------
//   Adds "Thesaurus" option to AbiWord's Tools Menu.
//
static void
AiksaurusABI_addToMenus()
{
    // First we need to get a pointer to the application itself.
    XAP_App *pApp = XAP_App::getApp();

    
    // Create an EditMethod that will link our method's name with
    // it's callback function.  This is used to link the name to 
    // the callback.
    EV_EditMethod *myEditMethod = new EV_EditMethod(
        "AiksaurusABI_invoke",  // name of callback function
        AiksaurusABI_invoke,    // callback function itself.
        0,                      // no additional data required.
        ""                      // description -- allegedly never used for anything
    );
   
    // Now we need to get the EditMethod container for the application.
    // This holds a series of Edit Methods and links names to callbacks.
    EV_EditMethodContainer* pEMC = pApp->getEditMethodContainer();
    
    // We have to add our EditMethod to the application's EditMethodList
    // so that the application will know what callback to call when a call
    // to "AiksaurusABI_invoke" is received.
    pEMC->addEditMethod(myEditMethod);
  

    // Now we need to grab an ActionSet.  This is going to be used later
    // on in our for loop.  Take a look near the bottom.
    EV_Menu_ActionSet* pActionSet = pApp->getMenuActionSet();

    
    // We need to go through and add the menu element to each "frame" 
    // of the application.  We can iterate through the frames by doing
    // XAP_App::getFrameCount() to tell us how many frames there are,
    // then calling XAP_App::getFrame(i) to get the i-th frame.
    int frameCount = pApp->getFrameCount();
    
    for(int i = 0;i < frameCount;++i)
    {
        // Get the current frame that we're iterating through.
        XAP_Frame* pFrame = pApp->getFrame(i);

        // Get this frame's menu object.
        EV_Menu* pMenu = pFrame->getMainMenu();
        
        // Get the menu's layout object.  

        EV_Menu_Layout* pLayout = pMenu->getLayout();
        
        // Get the menu's label set.  Again we need to modify it so we
        // are forced to cast away const-ness.  
        EV_Menu_LabelSet* pLabelSet = pMenu->getLabelSet();

        
        // Figure out where the tools menu is.
        UT_uint32 toolsId = pLayout->getLayoutIndex(
                EV_searchMenuLabel(*pLabelSet, "&Word Count")
        );
                   
        // Get a new ID so that we can add ourself to this menu.
        XAP_Menu_Id id = pLayout->addLayoutItem(
            ++toolsId,          // position to add menu item to
            EV_MLF_Normal       // i don't remember what this is for.
        );
      
        
        
        // Create the AikSaurus menu label.
        EV_Menu_Label* myLabel = new EV_Menu_Label(
            id,                         // id that the layout said we could use.
            AiksaurusABI_MenuLabel,     // the label that we want the menu option to have.
            AiksaurusABI_MenuTooltip    // the toolltip text to display for this option
        );
        
        // add the label to the label set so the user can see "Thesaurus"
        pLabelSet->addLabel(myLabel);
       
        
        // Create the Action that will be called.
        EV_Menu_Action* myAction = new EV_Menu_Action(
            id,                     // id that the layout said we could use
            0,                      // no, we don't have a sub menu.
            1,                      // yes, we raise a dialog.
            0,                      // no, we don't have a checkbox.
            "AiksaurusABI_invoke",  // name of callback function to call.
            NULL,                   // don't know/care what this is for
            NULL                    // don't know/care what this is for
        );

        // Now what we need to do is add this particular action to the ActionSet
        // of the application.  This forms the link between our new ID that we 
        // got for this particular frame with the EditMethod that knows how to 
        // call our callback function.  (We got our pActionSet pointer right 
        // before entering the loop.)
        pActionSet->addAction(myAction);
    }
}

    
// -----------------------------------------------------------------------
//
//      Abiword Plugin Interface 
//
// -----------------------------------------------------------------------
    
ABI_FAR_CALL extern "C"

int abi_plugin_register (XAP_ModuleInfo * mi)
{
    mi->name = "Aiksaurus";
    mi->desc = "English-language thesaurus based on the AikSaurus library: "
               "http://www.aiksaurus.com/";
    mi->version = ABI_VERSION_STRING;
    mi->author = "Jared Davis (jared@aiksaurus.com)";
    mi->usage = "No Usage";
    
    // Set title of thesaurus to look like it is AbiWord's own.
    AiksaurusGTK_setTitle("AbiWord Thesaurus");

    // Add the thesaurus to AbiWord's menus.
    AiksaurusABI_addToMenus();
    
    return 1;
}


ABI_FAR_CALL extern "C"
int abi_plugin_unregister (XAP_ModuleInfo * mi)
{
    mi->name = 0;
    mi->desc = 0;
    mi->version = 0;
    mi->author = 0;
    mi->usage = 0;
    return 1;
}


ABI_FAR_CALL extern "C"
int abi_plugin_supports_version (UT_uint32 major, UT_uint32 minor, UT_uint32 release)
{
    return 1; 
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
bool 
AiksaurusABI_invoke(AV_View* v, EV_EditMethodCallData *d)
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

    return true;
}
