#include "Replacebar.h"

#ifndef QLAYOUT_H
    #include <qlayout.h>
#endif

#ifndef QLABEL_H
    #include <qlabel.h>
#endif

#ifndef QLINEEDIT_H
    #include <qlineedit.h>
#endif

#ifndef QPUSHBUTTON_H
    #include <qpushbutton.h>
#endif

namespace AiksaurusQT_impl
{
    //
    // Replacebar::_destruct()
    //   Basically our destructor, destroy all our objects.
    //
    void Replacebar::_destruct()
    {
        delete d_layout_ptr;
        delete d_replacewith_ptr;
        delete d_replacement_ptr;
        delete d_replacebutton_ptr;
        delete d_cancelbutton_ptr;
    }


    //
    // Replacebar::Replacebar()
    //   Constructor, get a parent and a mediator.
    //
    Replacebar::Replacebar(QWidget* parent)
    : QWidget(parent)
    {
        try
        {
            d_layout_ptr = 0;
            d_replacewith_ptr = 0;
            d_replacement_ptr = 0;
            d_replacebutton_ptr = 0;
            d_cancelbutton_ptr = 0;

            d_layout_ptr = new QHBoxLayout(this, 0, 3);
            d_replacewith_ptr = new QLabel("Replace with: ", this);
            d_replacement_ptr = new QLineEdit(this);
            d_replacebutton_ptr = new QPushButton("Replace", this);
            d_cancelbutton_ptr = new QPushButton("Cancel", this);

            d_replacement_ptr->setMinimumSize(140, 1);

            d_layout_ptr->addSpacing(8);
            d_layout_ptr->addWidget(d_replacewith_ptr);
            d_layout_ptr->addWidget(d_replacement_ptr);
            d_layout_ptr->addStretch(1);
            d_layout_ptr->addSpacing(16);
            d_layout_ptr->addWidget(d_replacebutton_ptr);
            d_layout_ptr->addStretch();
            d_layout_ptr->addWidget(d_cancelbutton_ptr);
            d_layout_ptr->addSpacing(3);

            connect(d_replacement_ptr, SIGNAL(returnPressed()),
                    this, SLOT(_replaceClicked()));

            connect(d_replacebutton_ptr, SIGNAL(clicked()),
                    this, SLOT(_replaceClicked()));

            connect(d_cancelbutton_ptr, SIGNAL(clicked()),
                    this, SLOT(_cancelClicked()));
        }

        catch(...)
        {
            _destruct();
            throw;
        }
    }


    //
    // Replacebar::~Replacebar()
    //   Destroy the replacebar.
    //
    Replacebar::~Replacebar()
    {
        _destruct();
    }


    //
    // Replacebar::_replaceClicked()
    //   call the replace event on our mediator.
    //
    void Replacebar::_replaceClicked()
    {
        const char* word = getText();
        emit replace(word);
    }


    //
    // Replacebar::_cancelClicked()
    //   call the cancel event on our mediator.
    //
    void Replacebar::_cancelClicked()
    {
        emit cancel();
    }


    //
    // Replacebar::getText()
    //   return the current text from our "replace with" box.
    //
    const char* Replacebar::getText() const
    {
        return d_replacement_ptr->text();
    }


    //
    // Replacebar::setText()
    //   set the text of our "replace with" box to something else.
    //
    void Replacebar::setText(const char* text)
    {
        d_replacement_ptr->setText(text);
    }
}
