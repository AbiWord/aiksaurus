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

#ifndef INCLUDED_JARED_GPL_KAIKSAURUS_H
#define INCLUDED_JARED_GPL_KAIKSAURUS_H

// we inherit from kmainwindow, so we have no choice but to include it.
#include <kmainwindow.h>


// forward declarations of needed classes.
// use these instead of #include to cut down on compilation time for anyone
// who includes this header.
class AikSaurus;
class AikSaurusHistory;

class QLabel;
class QToolButton;
class QToolBar;
class QTabBar;
class QTab;
class QListBox;
class QVGroupBox;
class QStrList;
class QListBoxItem;

class KHistoryCombo;



// 
// KAikSaurus Class
// ----------------
//   Graphical AikSaurus Interface with KDE
//  
class KAikSaurus : public KMainWindow
{
	Q_OBJECT

	private:

	// Globals
	
		// Numeric tab identifiers (constants).
		static const int Noun;
		static const int Verb;
		static const int Adjective;
		static const int Adverb;
		static const int Other;
		static const int Unknown;
		static const int Similar;
	
		enum { NumTabs = 7 };
		
	// Data Structure
	
		AikSaurus			// the thesaurus itself
			*d_thesaurus;
		
		AikSaurusHistory 		// our back/forward history
			*d_history;
	
		QStrList
			*d_wordLists[NumTabs];
		
			
	// User Interface Elements
	
		QToolBar 		// the toolbar itself
			*d_toolbar;
		
		KHistoryCombo 		// the "look up" entry box
			*d_lookup;
		
		QLabel 			// the words "look up"
			*d_lookupLabel;

		QToolButton 		// toolbar buttons
			*d_forward, 
			*d_back, 
			*d_search;

		QTabBar 		// our tab strip
			*d_tabBar;
	
		QTab		
			*d_tabs[NumTabs]; 
	
		int	
			d_tabIDs[NumTabs];
			
		QListBox 		// the current wordlist displayed
			*d_wordList;
			
		QVGroupBox 		// groups word list with tab strip.
			*d_mainWidget;
		
		int d_lastTab;
		
		void checkHistoryButtons();
		void checkThesaurusStatus();
		void clearWordLists();
		void createToolbar();
		void recreateTabs();
		void destroyTabs();
		void doSearchCode();
			
	private slots: 

		void goBack();
		void goForward();
		void doSearch();
		
		void changedFindString(const QString& str);
		void selectedTab(int tid);
		
		void listClicked(QListBoxItem* item);
		void listDoubleClicked(QListBoxItem* item);
		
	public:

		KAikSaurus();
		~KAikSaurus();
};

#endif // INCLUDED_JARED_GPL_KAIKSAURUS_H
