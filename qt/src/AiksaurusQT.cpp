#include "AiksaurusQT.h"
#include "Toolbar.h"
#include "Display.h"
#include "Replacebar.h"
#include <qlayout.h>

namespace AiksaurusQT_impl
{
    Dialog::Dialog(QWidget* parent, const char* name, bool modal, WFlags f)
        : QDialog(parent, name, modal, f)
    {
        d_layout_ptr = new QVBoxLayout(this, 0, 3);
        d_toolbar_ptr = new Toolbar(this);
        d_display_ptr = new Display(this);
        d_replacebar_ptr = new Replacebar(this);

        d_display_ptr->resize(330, 200);
        d_layout_ptr->addSpacing(3);
        d_layout_ptr->addWidget(d_toolbar_ptr);
        d_layout_ptr->addWidget(d_display_ptr);
        d_layout_ptr->addWidget(d_replacebar_ptr);
        d_layout_ptr->addSpacing(3);

        connect(d_toolbar_ptr, SIGNAL(newSearch(const char*)),
                this, SLOT(doSearch(const char*)));

        connect(d_display_ptr, SIGNAL(selectWord(const char*)),
                this, SLOT(_eventSelectWord(const char*)));

        connect(d_display_ptr, SIGNAL(newSearch(const char*)),
                this, SLOT(doSearch(const char*)));

        connect(d_replacebar_ptr, SIGNAL(cancel()),
                this, SLOT(_eventCancel()));

        connect(d_replacebar_ptr, SIGNAL(replace(const char*)),
                this, SLOT(_eventReplace(const char*)));
    }

    void Dialog::hideReplacebar()
    {
        d_replacebar_ptr->hide();
    }

    void Dialog::showReplacebar()
    {
        d_replacebar_ptr->show();
    }

    Dialog::~Dialog()
    {
        delete d_layout_ptr;
        delete d_toolbar_ptr;
        delete d_display_ptr;
        delete d_replacebar_ptr;
    }

    void Dialog::_eventSelectWord(const char* word)
    {
        d_replacebar_ptr->setText(word);
    }

    void Dialog::doSearch(const char* word)
    {
        d_toolbar_ptr->doSearch(word);
        d_display_ptr->doSearch(word);
        d_replacebar_ptr->setText(word);
    }

    void Dialog::done(int r)
    {
        if (!r)
            emit cancel();

        QDialog::done(r);
    }

    void Dialog::_eventReplace(const char* repl)
    {
        emit replace(repl);
        done(1);
    }

    void Dialog::_eventCancel()
    {
        done(0);
    }
}
