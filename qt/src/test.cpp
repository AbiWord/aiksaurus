#include "test.h"
#include <qapp.h>
#include <iostream>
using namespace std;

void
MyCustomWidget::_buttonClicked()
{
    d_button_ptr->hide();
    delete d_button_ptr;

//    d_button_ptr = new QPushButton("I LIVE AGAIN!", this);
//    d_layout_ptr->addWidget(d_button_ptr);
//    d_button_ptr->show();
}

MyCustomWidget::MyCustomWidget(QWidget* parent = 0) : QWidget(parent)
{
    d_button_ptr = new QPushButton("About to Die", this);

    d_layout_ptr = new QHBoxLayout(this);
    d_layout_ptr->addWidget(d_button_ptr);

    connect(d_button_ptr, SIGNAL(clicked()),
            this, SLOT(_buttonClicked()));
}

MyCustomWidget::~MyCustomWidget()
{
    delete d_button_ptr;
    delete d_layout_ptr;
}

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MyCustomWidget foo;

    app.setMainWidget( &foo );

    foo.resize(330, 240);
    foo.show();

    return app.exec();
}
