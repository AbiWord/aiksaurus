#include "Meaning.h"
#include "Display.h"
#include <qlayout.h>
#include <qhbox.h>
#include <qlistbox.h>
#include <qlabel.h>
//#include <iostream>
//using namespace std;

namespace AiksaurusQT_impl
{
    const QColor Meaning::s_bgcolor(240, 240, 224);

    static void ucwords(QString& str)
    {
        bool ws = true;
        for(int i = 0;i < static_cast<int>(str.length());++i)
        {
            if (str[i].isSpace())
                ws = true;

            else if (ws)
            {
                str[i] = str[i].upper();
                ws = false;
            }
        }
    }


    void Meaning::_destruct()
    {
        delete d_masterlayout_ptr;
        delete d_mainlayout_ptr;
        delete d_label_ptr;
        for(unsigned int i = 0;i < d_lists.size();++i)
            delete d_lists[i];
    }


    void Meaning::_unselectListsExcept(QListBoxItem* item)
    {
        for(unsigned int i = 0;i < d_lists.size();++i)
        {
            if (d_lists[i]->currentText() != item->text())
                d_lists[i]->clearSelection();
        }
    }

    void Meaning::_itemSelected(QListBoxItem* item)
    {
        if (item) // <-- important!
            emit itemSelected(item);
    }

    void Meaning::_itemChosen(QListBoxItem* item)
    {
        emit itemChosen(item);
    }

    void Meaning::_createLists()
    {
        int i;
        for(i = 0;i < 4;++i)
        {
            d_lists.push_back( new QListBox(d_mainlayout_ptr) );
            d_lists[i]->setFont( QFont("arial", 12) );
            d_lists[i]->setFrameShape(QFrame::NoFrame);
            d_lists[i]->setHScrollBarMode(QScrollView::AlwaysOff);
            connect(d_lists[i], SIGNAL(pressed(QListBoxItem*)),
                    this, SLOT(_itemSelected(QListBoxItem*)));

            connect(d_lists[i], SIGNAL(highlighted(QListBoxItem*)),
                    this, SLOT(_itemSelected(QListBoxItem*)));

            connect(d_lists[i], SIGNAL(doubleClicked(QListBoxItem*)),
                    this, SLOT(_itemChosen(QListBoxItem*)));
        }

        int n = d_words.size(),
            q = n / 4,
            r = n % 4;

        int stop1, stop2, stop3;

        switch(r)
        {
            case 0:
                stop1 = q;
                stop2 = stop1 + q;
                stop3 = stop2 + q;
                break;
            case 1:
                stop1 = q + 1;
                stop2 = stop1 + q;
                stop3 = stop2 + q;
                break;
            case 2:
                stop1 = q + 1;
                stop2 = stop1 + q + 1;
                stop3 = stop2 + q;
                break;
            default:
                stop1 = q + 1;
                stop2 = stop1 + q + 1;
                stop3 = stop2 + q + 1;
                break;
        }

        for(i = 0; i < stop1; ++i)
            d_lists[0]->insertItem(d_words[i]);

        for(; i < stop2; ++i)
            d_lists[1]->insertItem(d_words[i]);

        for(; i < stop3; ++i)
            d_lists[2]->insertItem(d_words[i]);

        for(; i < static_cast<int>(d_words.size()); ++i)
            d_lists[3]->insertItem(d_words[i]);

        for(i = 0;i < 4;++i)
        {
            d_lists[i]->setMinimumSize(80, d_lists[i]->numRows() * d_lists[i]->itemHeight());
        }
    }


    Meaning::Meaning(const QString& title, const vector<QString>& words, QWidget* parent)
        : QWidget(parent),
          d_title(" " + title),
          d_words(words)
    {
        try
        {
            ucwords(d_title);

            d_masterlayout_ptr = new QVBoxLayout(this, 0, 2);
            d_mainlayout_ptr = new QHBox(this);

            d_label_ptr = new QLabel(d_title, this);

            QPalette pal;
            pal.setColor( QColorGroup::Foreground, QColor(100, 0, 0) );
            d_label_ptr->setPalette(pal);

            d_label_ptr->setBackgroundColor(s_bgcolor);
            d_label_ptr->setFont( QFont("arial", 14, QFont::DemiBold) );

            _createLists();

            setBackgroundColor(s_bgcolor);

            d_masterlayout_ptr->addWidget(d_label_ptr);
            d_masterlayout_ptr->addWidget(d_mainlayout_ptr);
        }
        catch(...)
        {
            _destruct();
            throw;
        }
    }

    Meaning::~Meaning()
    {
        //cout << "Welcome to the Meaning::~Meaning." << endl;
        // TODO: FIX THIS!!! _destruct();
    }

    QSize Meaning::sizeHint() const
    {
        return QSize(0, d_label_ptr->height() + d_mainlayout_ptr->height());
    }
}
