#ifndef INCLUDED_AIKSAURUS_QT_H
#define INCLUDED_AIKSAURUS_QT_H

#include <qdialog.h>
class QVBoxLayout;

namespace AiksaurusQT_impl
{
    class Toolbar;
    class Display;
    class Replacebar;

    class Dialog : public QDialog
    {
        Q_OBJECT

        private:
            Dialog(const Dialog& rhs);
            Dialog& operator=(const Dialog& rhs);

            QVBoxLayout* d_layout_ptr;
            Toolbar*     d_toolbar_ptr;
            Display*     d_display_ptr;
            Replacebar*  d_replacebar_ptr;

        private slots:
            void _eventReplace(const char* replacement);
            void _eventCancel();
            void _eventSelectWord(const char* word);


        protected slots:
            virtual void done(int);


        public:
            Dialog(QWidget* parent = 0, const char* name = 0, bool modal = false, WFlags f = 0);
            virtual ~Dialog();

            void hideReplacebar();
            void showReplacebar();

        signals:
            void replace(const char* word);
            void cancel();


        public slots:
            void doSearch(const char* word);
    };

}

typedef AiksaurusQT_impl::Dialog AiksaurusQT;

#endif // INCLUDED_AIKSAURUS_QT_H
