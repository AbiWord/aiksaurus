/*
 * Kaiksaur - A KDE interface to AikSaurus
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
 *
 */

// Header file for the class that we're implementing.
#include "KAikSaurImpl.h"

// Thesaurus header for AikSaurus library itself.
#include <AikSaurus.h>

// History to keep track of our searches with.
#include "QAikSaurusHistory.h"

// KApplicaiton itself for our main function.
#include <kapp.h>

// Kcombobox needed for our lookup bar.
#include <kcombobox.h>

// Toolbar stuff for our toolbar. 
#include <qtoolbar.h>
#include <qtoolbutton.h>

// Icons in our back/forward/search buttons.
#include <qpixmap.h>

// Status bar for our window, useful for error reporting.
#include <qstatusbar.h>

// Tab bar needed for the nouns/verbs/etc. tab strip.
#include <qtabbar.h>

// Listbox used to list all the words that we return.
#include <qlistbox.h>

// QVgroupbox used to group the tabs above the listbox.  Basically lays our 
// our window for us.
#include <qvgroupbox.h>

#include <iostream>
#include <vector>
#include <cassert>
#include <strstream>
#include <string>


using namespace std;

const int KAikSaurus::Noun 	= 0;
const int KAikSaurus::Verb 	= 1;
const int KAikSaurus::Adjective	= 2;
const int KAikSaurus::Adverb 	= 3;
const int KAikSaurus::Other 	= 4;
const int KAikSaurus::Unknown 	= 5;
const int KAikSaurus::Similar 	= 6;


// ----------------------------------------------------------------------------
// KAikSaurus Helper Functions
// ----------------------------------------------------------------------------
//
//   The following functions are simple helper functions that are just used 
//   throughout the class.  Understanding their exact implementation is 
//   generally unnecessary.
//
// ----------------------------------------------------------------------------


//
// KAikSaurus::clearWordLists()
// ----------------------------
//   Simple helper function to clear out all of the word lists.
//
void KAikSaurus::clearWordLists()
{
	for(int i = 0;i < NumTabs;++i)
		d_wordLists[i]->clear();
}


//
// KAikSaurus::checkThesaurusStatus()
// ----------------------------------
//   Simple helper function to set our status bar's message to reflect
//   the current state of our AikSaurus object.
//   
//   If everything's ok, we'll display the message: "Ready."
//
void KAikSaurus::checkThesaurusStatus()
{
	QString status(d_thesaurus->error());
	
	if (status == "")
		status = "Ready.";
	
	statusBar()->message(status);
}


//
// KAikSaurus::checkHistoryButtons()
// ---------------------------------
//   Simple helper function to disable/enable the forward and back 
//   buttons based on if there is history in that direction.
//   
void KAikSaurus::checkHistoryButtons()
{
	d_back->setEnabled( !d_history->atBegin() );
	d_forward->setEnabled( !d_history->atEnd() );
}


//
// KAikSaurus::destroyTabs()
// -------------------------
//   Safely remove all the tabs and nullify their pointers, so that we can 
//   recreate them without having to worry.
//   
void KAikSaurus::destroyTabs()
{
	for(int i = 0;i < NumTabs;++i)
	{
		// clear out tab id's so that if our tabs are recreated,
		// we don't have old id's getting screwed up in the process.
		d_tabIDs[i] = -1;

		// now we will remove the tabs that exist from the tab bar.
		// removeTab() allegedly deletes these automatically, so we don't
		// need to call delete on them.
		if (d_tabs[i] != NULL)
		{
			d_tabBar->removeTab(d_tabs[i]);
			d_tabs[i] = NULL;
		}
	}
}








// ----------------------------------------------------------------------------
// KAikSaurus Interface Functions
// ----------------------------------------------------------------------------
//
//   The following functions deal with user-interface issues, i.e. handling
//   events like mouse clicks and button pushes.
//
// ----------------------------------------------------------------------------


//
// KAikSaurus::goBack()
// --------------------
//   This is called when the "back" button is pushed.  We will go back to 
//   the previous search.
//   
void KAikSaurus::goBack() 
{
	assert(!d_history->atBegin());

	const QString& back = d_history->back();

	d_lookup->setEditText(back);

	doSearchCode();

	checkHistoryButtons();
}


//
// KAikSaurus::goForward()
// -----------------------
//   This is called when the "forward" button is pushed.  We will go forward
//   to the next search.
//  
void KAikSaurus::goForward()
{
	assert(!d_history->atEnd());
	
	const QString& next = d_history->forward();
	
	d_lookup->setEditText(next);
	
	doSearchCode();

	checkHistoryButtons();
}


//
// KAikSaurus::selectedTab()
// -------------------------
//   This is called when the user clicks on a new tab, such as "nouns" or 
//   "verbs".  We need to replace the entries in the word list with the 
//   correct set of words for the new tab.
//   
void KAikSaurus::selectedTab(int id)
{
	d_wordList->clear();
	
	for(int i = 0;i < NumTabs;++i)
	{
		if (id == d_tabIDs[i])
		{
			d_lastTab = (i == Similar) ? (Noun) : (i);
			d_wordList->insertStrList(d_wordLists[i]);
			break;
		}
	}
}


//
// KAikSaurus::listClicked()
// -------------------------
//   This is called when the user clicks a word in our words list.  We 
//   should do nothing right now, but subclasses probably want to 
//   redefine the behavior of this function.
//   
void KAikSaurus::listClicked(QListBoxItem *item)
{
	// don't know what to do here.
}


// 
// KAikSaurus::listDoubleClicked()
// -------------------------------
//   This is called when a user double-clicks a word in the words list.
//   We need to conduct a new search for the item that they double-
//   clicked on.
//   
void KAikSaurus::listDoubleClicked(QListBoxItem *item)
{
	QString str(item->text());

	d_lookup->setEditText(str.stripWhiteSpace());

	doSearch();
}


//
// KAikSaurus::doSearch()
// ----------------------
//   This function is called when the user clicks the "search" button.
//   It is also invoked by our own changedFindString() function.  We 
//   need to perform a search for the new word.
//   
void KAikSaurus::doSearch()
{
	if (d_lookup->currentText() == "")
		return;
	
	d_history->search( d_lookup->currentText() );

	checkHistoryButtons();

	doSearchCode();
}


// 
// KAikSaurus::changedFindString()
// ------------------------------
//   This function is called when the enter-key is pressed while the
//   user is in the 'look up' bar.  We need to do a search, so we'll 
//   just execute the doSearch() function.
//
void KAikSaurus::changedFindString(const QString& str)
{
	doSearch();
}















// ----------------------------------------------------------------------------
// KAikSaurus Initialization Functions
// ----------------------------------------------------------------------------
//
//   The following functions deal with startup and initialization issues, i.e.
//   creating the toolbars and statusbars and so forth.  We also put the 
//   destructor here.
//
// ----------------------------------------------------------------------------


//
// KAikSaurus::createToolbar()
// ---------------------------
//   Initializes the toolbar and adds it to the window.  The toolbar includes
//   the forward and back button, look-up bar, and search button.
//   
void KAikSaurus::createToolbar()
{
	d_toolbar = new QToolBar("Kaiksaur Toolbar", this);
	d_toolbar->setHorizontalStretchable(true);
	
	
	// load our icons for back, forward, and search buttons.
	QPixmap backArrow("back.xpm");
	QPixmap forwardArrow("forward.xpm");
	QPixmap search("search.xpm");
	
	
	// Create the back button, connecting it to the goBack() slot.
	d_back = new QToolButton(
		backArrow, "Back", "Returns to the previous search.", 
		this, SLOT(goBack()), d_toolbar, "Back"
	);
	
	
	// Create the forward button, connecting it to the goForward() slot.
	d_forward = new QToolButton(
		forwardArrow, "Forward", "Advances to the next search.", 
		this, SLOT(goForward()), d_toolbar, "Forward"
	);


	// Now we create a label that says "Look up:" in front of the lookup
	// bar.  The extra spaces give us a little padding and just generally 
	// makes it look better.
	d_lookupLabel = new QLabel(d_toolbar, "Look Up Label");
	d_lookupLabel->setText("  Look Up: ");
	

	// We now are going to make the lookup-bar itself.   
	d_lookup = new KHistoryCombo(true, d_toolbar, "Look Up Bar");
	d_lookup->setEditable(true);
	d_lookup->setInsertionPolicy(QComboBox::AtTop);
	d_lookup->setDuplicatesEnabled(false);
	d_lookup->setMaxCount(15);

	// TO DO: GET THIS CODE WORKING
	// we should have the bar use auto-completion.  but, it doesn't right 
	// now.  figure out why and fix it.
	d_lookup->setAutoCompletion(true);
	d_lookup->setCompletionMode(KGlobalSettings::CompletionAuto);

	// Finally, connect the lookup bar's enter-key to the search function.
	QObject::connect(d_lookup, SIGNAL(returnPressed(const QString&)), 
			this, SLOT(changedFindString(const QString&)));
	

	// Lastly, create the search button and connect it to the search slot.
	d_search = new QToolButton(
		search, "Search", "Searches for a word.", 
		this, SLOT(doSearch()), d_toolbar, "Search"
	);
	
	// we want the address-bar like thing to fill up the whole toolbar
	// except for the buttons.
	d_toolbar->setStretchableWidget(d_lookup);
	
	// our toolbar is finished: add it to the window.	
	addToolBar(d_toolbar);

	// make it so that the toolbar can only be horizontal at the top.
	// vertical looks really bad with the search-entry bar.
	setToolBarsMovable(false);

	// now, this makes sure that our forward and back buttons are 
	// disabled if there is nowhere to go.
	checkHistoryButtons();
}


// 
// KAikSaurus::KAikSaurus()
// ------------------------
//   Constructor.  Initialize everything.  Build a toolbar.  Display some
//   sort of welcome screen.
//   
KAikSaurus::KAikSaurus() 
:
  // first initialize our superclass's stuff.
  KMainWindow(),

  // initialize the thesaurus itself.
  d_thesaurus(new AikSaurus),
 
  // initialize a history to manage our forward/back buttons.
  d_history(new AikSaurusHistory())
{
	setCaption("KAikSaurus");
	setGeometry(10,10,450,300);

	for(int i = 0;i < NumTabs;++i)
	{
		d_tabs[i] = NULL;
		d_tabIDs[i] = -1;
		d_wordLists[i] = new QStrList();
	}

	d_lastTab = Noun;
	
	// Create the status bar.  the loading message is, frankly, worthless,
	// but it does suppress a compiler warning that claims we aren't using 
	// this variable for anything.
	QStatusBar *status = new QStatusBar(this, "Status Bar");
	status->message("Loading."); 
	
	
	// Create the tool bar and all its associated buttons, etc.
	createToolbar();

	
	// Create the main widget.  we use a vertical grouping box to put the 
	// tab strip on top of the word lists.
	d_mainWidget = new QVGroupBox(this, "Main Widget");

	
	// TO DO: replace with some sort of startup screen.
	d_tabBar = new QTabBar(d_mainWidget, "Results Tab Bar");
	d_tabBar->setShape(QTabBar::RoundedAbove);

	connect(d_tabBar, SIGNAL(selected(int)), this, SLOT(selectedTab(int)));

	d_tabs[Noun] = new QTab("Awaiting Query");
	d_tabBar->addTab(d_tabs[Noun]);
	
	d_wordList = new QListBox(d_mainWidget, "Word List");
	d_wordList->setColumnMode(QListBox::FitToWidth);
	d_wordList->setVariableWidth(false);

	// set up our word list to tell us when it's been clicked on.
	connect(d_wordList, SIGNAL(clicked(QListBoxItem*)), 
			this, SLOT(listClicked(QListBoxItem*)));
	
	connect(d_wordList, SIGNAL(doubleClicked(QListBoxItem*)), 
			this, SLOT(listDoubleClicked(QListBoxItem*)));

	
	// Setting central widget to our grouping box expands the grouping box
	// to fill the space allotted by the window, and gives us exactly the
	// interface that we want.
	this->setCentralWidget(d_mainWidget);
	
	
	// Finally, let's set our status message to reflect the true nature of
	// our underlying implementation.
	checkThesaurusStatus();
}


//
// KAikSaurus::~KAikSaurus()
// -------------------------
//   Our destructor needs to clean up all the junk we've allocatd.
//   
KAikSaurus::~KAikSaurus()
{
	// TO DO: destruct all this nonsense properly.
}










void KAikSaurus::recreateTabs()
{
	static string labels[6] = 
	{
		" &Nouns",
		" &Verbs",
		" &Adjectives",
		" A&dverbs",
		" &Others",
		" &Unclassified"
	};
	
	destroyTabs();
	
	
	string sizes[6];
	for(int i = 0;i < 6;++i)
	{
		strstream ss;
		ss << d_wordLists[i]->count();
		ss >> sizes[i];
		sizes[i] += labels[i];
	}

//	QTab* current = NULL;		
	bool showsim = true;
	
	for(int i = 0;i < 6;++i)
	{
		if (d_wordLists[i]->count())
		{
			showsim = false;
			d_tabs[i] = new QTab(sizes[i].c_str());
		
//			if (!current)
//				current = d_tabs[i];

			d_tabIDs[i] = d_tabBar->addTab(d_tabs[i]);
		}
	}	
	
	if (showsim)
	{
		d_tabs[Similar] = new QTab("No Matches found.  Similar words:");

//		if (!current)
//			current = d_tabs[Similar];

		d_tabIDs[Similar] = d_tabBar->addTab(d_tabs[Similar]);
	}
	
	
	
	d_tabBar->setCurrentTab(d_tabIDs[d_lastTab]);
	selectedTab( d_tabBar->currentTab() );
}


	


void KAikSaurus::doSearchCode()
{
	const QString& findme(d_lookup->currentText());
	
	// This function should perform a search and list the results.
	// It should NOT modify the search history, that's done outside.

	clearWordLists();
	
	if (d_thesaurus->find(findme))
	{
		char pos;
		
		for(const char* res = d_thesaurus->next(pos); res[0] != '\0'; res = d_thesaurus->next(pos))
		{
			QString addme(res);
			addme += "   "; // add some extra space to improve looks.
			if (pos & AikSaurus::Noun) 	d_wordLists[Noun]->append(addme);
			if (pos & AikSaurus::Verb) 	d_wordLists[Verb]->append(addme);
			if (pos & AikSaurus::Adverb) 	d_wordLists[Adverb]->append(addme);
			if (pos & AikSaurus::Adjective) d_wordLists[Adjective]->append(addme);
			if (pos & AikSaurus::Other) 	d_wordLists[Other]->append(addme);
			if (pos & AikSaurus::Unknown) 	d_wordLists[Unknown]->append(addme);
		}
		
	}

	for(const char* sim = d_thesaurus->similar(); sim[0] != '\0';sim = d_thesaurus->similar())
	{
		QString addme(sim);
		addme += "   "; // add some extra space to improve looks.
		
		d_wordLists[Similar]->append(addme);
	}
	
	recreateTabs();
	
	checkThesaurusStatus();
}



int main(int argc, char **argv)
{
	KApplication a( argc, argv, "Kaiksaur" );

	KAikSaurus *interface = new KAikSaurus();

	a.setMainWidget(interface);
	interface->show();

	return a.exec();
}







