#ifndef INCLUDED_DISPLAY_H
#define INCLUDED_DISPLAY_H

#include <Aiksaurus.h>
#include <qscrollview.h>
#include <vector>

class QVBoxLayout;
class QListBoxItem;

namespace AiksaurusQT_impl
{
    class Meaning;
    class Display : public QScrollView
    {
        Q_OBJECT

        friend class Meaning;

        private:
            Display(const Display& rhs);
            Display& operator=(const Display& rhs);

            Aiksaurus d_thesaurus;

            QWidget d_box;
            QVBoxLayout *d_layout_ptr;

            std::vector<Meaning*> d_meanings;

            void _checkThesaurus();
            void _resetDisplay();
            void _displayAlternatives();
            void _displayResults(const QString& word);
            void _createMeaning(const QString& title, const vector<QString>& words);

        private slots:
            void _itemSelected(QListBoxItem* item);
            void _itemChosen(QListBoxItem* item);


        signals:
            void selectWord(const char* word);
            void newSearch(const char* word);


        public:
            Display(QWidget* parent);
            virtual ~Display();

            void doSearch(const char* word);
    };
}

#endif // INCLUDED_DISPLAY_H
