#include "launcher.h"
#include "AiksaurusQT.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <iostream>
#include <cctype>
using namespace std;

void Launcher::_currentWordPosition(int& left, int& length)
{
    const QString& text = d_edit_ptr->text();
    left = d_edit_ptr->cursorPosition();
    int right = d_edit_ptr->cursorPosition();

    // go as far left as we can.
    while( left > 0 )
    {
        if (isspace(text[left]) || ispunct(text[left]))
        {
            ++left;
            break;
        }

        --left;
    }

    // go as far right as we can.
    while( right < static_cast<int>(text.length()) )
    {
        if (isspace(text[right]) || ispunct(text[right]))
        {
            ++right;
            break;
        }
        ++right;
    }

    length = right - left;
}

QString Launcher::_getCurrentWord()
{
    QString ret;

    if (d_edit_ptr->hasMarkedText())
        ret = d_edit_ptr->markedText().stripWhiteSpace();

    else
    {
        int left, length;
        _currentWordPosition(left, length);
        ret = d_edit_ptr->text().mid(left, length).stripWhiteSpace();
    }

    cout << "  Current word is " << ret << endl;
    return ret;
}

void Launcher::_dialogCancel()
{
    cout << "Cancel Event Received" << endl;
}

void Launcher::_dialogReplace(const char* repl)
{
    cout << "Replace Event Received: Replacement is " << repl << ")" << endl;

    if (d_edit_ptr->hasMarkedText())
    {
        d_edit_ptr->del();
        QString text(d_edit_ptr->text());
        int position = d_edit_ptr->cursorPosition();
        text.insert(position, repl);
        d_edit_ptr->setText(text);
        d_edit_ptr->setCursorPosition(position + QString(repl).length());
    }

    else
    {
        int left, length;
        _currentWordPosition(left, length);

        d_edit_ptr->setCursorPosition(left);
        for(int i = 0;i < length-1;++i)
            d_edit_ptr->del();

        QString text(d_edit_ptr->text());
        text.insert(left, repl);
        d_edit_ptr->setText(text);
        d_edit_ptr->setCursorPosition(left + QString(repl).length());
    }
}

void Launcher::_modalClicked()
{
    cout << "Modal button clicked.  Launching modal thesaurus." << endl;
    AiksaurusQT thesaurus(this, "AiksaurusQT", true);
    thesaurus.setCaption("AiksaurusQT");
    thesaurus.doSearch(_getCurrentWord());
    thesaurus.resize(330, 240);

    connect(&thesaurus, SIGNAL(cancel()),
            this, SLOT(_dialogCancel()));

    connect(&thesaurus, SIGNAL(replace(const char*)),
            this, SLOT(_dialogReplace(const char*)));

    thesaurus.exec();
}

void Launcher::_modelessClicked()
{
    cout << "Modeless button clicked.  Launching modeless thesaurus." << endl;
    AiksaurusQT* thesaurus = new AiksaurusQT(this, "AiksaurusQT");
    thesaurus->setCaption("AiksaurusQT");
    thesaurus->doSearch(_getCurrentWord());
    thesaurus->resize(330, 240);
    thesaurus->show();

    connect(thesaurus, SIGNAL(cancel()),
            this, SLOT(_dialogCancel()));

    connect(thesaurus, SIGNAL(replace(const char*)),
            this, SLOT(_dialogReplace(const char*)));
}

Launcher::Launcher(QWidget* parent, const char* name)
: QWidget(parent, name)
{
    d_message_ptr = new QLabel(
       " AiksaurusQT Demonstration\n"
       " This program demonstrates modal vs. modeless thesaurus dialogs. \n\n"
       " Type some text (a few words) in the box below, then choose one of \n"
       " the buttons to activate the thesaurus dialog.  \n\n"
       " If you choose the modeless button, go ahead and click on the words \n"
       " in the edit box while the thesaurus is open and see what happens.\n\n"
       " You will not be able to click on them in modal mode.\n",
       this
    );

    d_edit_ptr = new QLineEdit("Freedom is the only law which genius knows. -- James Lowell", this);

    d_modal_ptr = new QPushButton("Modal", this);
    d_modeless_ptr = new QPushButton("Modeless", this);

    connect(d_modal_ptr, SIGNAL(clicked()),
            this, SLOT(_modalClicked()));

    connect(d_modeless_ptr, SIGNAL(clicked()),
            this, SLOT(_modelessClicked()));

    d_layout_ptr = new QVBoxLayout(this);
    d_layout_ptr->addWidget(d_message_ptr);
    d_layout_ptr->addWidget(d_edit_ptr);
    d_layout_ptr->addWidget(d_modal_ptr);
    d_layout_ptr->addWidget(d_modeless_ptr);
}

Launcher::~Launcher()
{
    delete d_layout_ptr;
    delete d_message_ptr;
    delete d_edit_ptr;
    delete d_modal_ptr;
    delete d_modeless_ptr;
}
