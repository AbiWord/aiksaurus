#ifndef INCLUDED_AIKSAURUS_QT_MEANING_H
#define INCLUDED_AIKSAURUS_QT_MEANING_H

#ifndef QWIDGET_H
    #include <qwidget.h>
#endif

#include <vector>

class QHBox;
class QVBoxLayout;
class QLabel;
class QListBox;
class QListBoxItem;

namespace AiksaurusQT_impl
{
    class Display;
    class Meaning : public QWidget
    {
        Q_OBJECT

        friend class Display;
        private:

            static const QColor s_bgcolor;

            Meaning(const Meaning& rhs);
            Meaning& operator=(const Meaning& rhs);
            void _destruct();
            void _createLists();
            void _unselectListsExcept(QListBoxItem* item);

            QString d_title;
            std::vector<QString> d_words;

            QVBoxLayout* d_masterlayout_ptr;
            QHBox* d_mainlayout_ptr;
            QLabel* d_label_ptr;
            std::vector<QListBox*> d_lists;

        private slots:
            void _itemSelected(QListBoxItem*);
            void _itemChosen(QListBoxItem*);


        signals:
            void itemSelected(QListBoxItem*);
            void itemChosen(QListBoxItem*);


        public:
            Meaning(const QString& title, const vector<QString>& words, QWidget* parent);
            virtual ~Meaning();

            virtual QSize sizeHint() const;
    };
}

#endif // INCLUDED_AIKSAURUS_QT_MEANING_H
