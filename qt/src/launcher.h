#ifndef INCLUDED_LAUNCHER_H
#define INCLUDED_LAUNCHER_H

#include <qwidget.h>
#include <qstring.h>
class QPushButton;
class QLabel;
class QVBoxLayout;
class QLineEdit;

class Launcher : public QWidget
{
    Q_OBJECT

    private:
        QLabel* d_message_ptr;
        QLineEdit* d_edit_ptr;
        QPushButton* d_modal_ptr;
        QPushButton* d_modeless_ptr;
        QVBoxLayout* d_layout_ptr;

        void _currentWordPosition(int& left, int& length);
        QString _getCurrentWord();

    private slots:
        void _modalClicked();
        void _modelessClicked();
        void _dialogCancel();
        void _dialogReplace(const char*);

    public:
        Launcher(QWidget* parent, const char* name);
        virtual ~Launcher();
};

#endif // INCLUDED_LAUNCHER_H
