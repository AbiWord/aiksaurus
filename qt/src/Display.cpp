#include "Display.h"
#include "Meaning.h"
#include <qlistbox.h>
#include <qlayout.h>
//#include <iostream>
//using namespace std;

namespace AiksaurusQT_impl
{
    Display::Display(QWidget* parent)
        : QScrollView(parent),
          d_box(viewport())
    {
        d_layout_ptr = 0;
        d_box.setBackgroundColor( QColor(255, 255, 255)  );
        addChild(&d_box);

        setResizePolicy(AutoOneFit);
        setMinimumWidth(330);
    }

    Display::~Display()
    {
        //cout << "Display::~Display called." << endl;
    }

    void Display::_resetDisplay()
    {
        if (d_layout_ptr)
            delete d_layout_ptr;
        d_layout_ptr = new QVBoxLayout(&d_box, 0, 0, "Display Layout");


        for(vector<Meaning*>::iterator i = d_meanings.begin(); i != d_meanings.end(); ++i)
        {
            Meaning* mean = *i;
            mean->hide();
            // TODO: FIX THIS!!! delete mean;
        }

        d_meanings.clear();
    }


    void Display::_checkThesaurus()
    {
        // TODO: handle this correctly
        assert(!d_thesaurus.error()[0]);
    }


    void Display::_createMeaning(const QString& title, const vector<QString>& words)
    {
        Meaning* meaning = new Meaning(title, words, &d_box);
        d_meanings.push_back(meaning);
        d_layout_ptr->addWidget(meaning);
        d_layout_ptr->setStretchFactor(meaning, 0);
        meaning->show();

        connect(meaning, SIGNAL(itemSelected(QListBoxItem*)),
                this, SLOT(_itemSelected(QListBoxItem*)));

        connect(meaning, SIGNAL(itemChosen(QListBoxItem*)),
                this, SLOT(_itemChosen(QListBoxItem*)));
    }

    void Display::_itemSelected(QListBoxItem* item)
    {
        for(unsigned int i = 0;i < d_meanings.size();++i)
        {
            d_meanings[i]->_unselectListsExcept(item);
        }

        const char* word = item->text();
        emit selectWord(word);
    }

    void Display::_itemChosen(QListBoxItem* item)
    {
        const char* word = item->text();
        emit newSearch(word);
    }

    void Display::_displayResults(const QString& word)
    {
        _checkThesaurus();

        QString title;
        vector<QString> words;

        int meaning, prev_meaning = -1;
        for(const char* r = d_thesaurus.next(meaning); r[0]; r = d_thesaurus.next(meaning))
        {
            if (meaning != prev_meaning)
            {
                if (prev_meaning != -1)
                {
                    _createMeaning(title, words);
                    words.clear();
                }

                prev_meaning = meaning;

                QString option1(r);
                QString option2(d_thesaurus.next(meaning));
                title = (option1.lower() != word.lower()) ? (option1) : (option2);

                r = d_thesaurus.next(meaning);
                _checkThesaurus();
            }

            words.push_back(r);
        }

        _createMeaning(title, words);

        d_layout_ptr->addStretch();
        d_layout_ptr->activate();
    }

    void Display::_displayAlternatives()
    {
        vector<QString> words;
        for(const char* r = d_thesaurus.similar(); r[0]; r = d_thesaurus.similar())
        {
            _checkThesaurus();
            words.push_back(r);
        }

        _createMeaning("No Synonyms Known.  Nearby words: ", words);

        d_layout_ptr->addStretch();
        d_layout_ptr->activate();
    }

    void Display::doSearch(const char* word)
    {
        _resetDisplay();
        _checkThesaurus();

        ensureVisible(0, 0);

        if (d_thesaurus.find(word))
            _displayResults(word);
        else
            _displayAlternatives();
    }
}
