#ifndef TEST_H
#define TEST_H

#include <qwidget.h>
#include <qpushbutton.h>
#include <qlayout.h>

class MyCustomWidget : public QWidget
{
    Q_OBJECT

    private:
        QPushButton* d_button_ptr;
        QHBoxLayout* d_layout_ptr;

    private slots:
        void _buttonClicked();

    public:
        MyCustomWidget(QWidget* parent = 0);
        virtual ~MyCustomWidget();
};

#endif // TEST_H
