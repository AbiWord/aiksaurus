#include "AiksaurusQT.h"
#include <qapp.h>
using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    AiksaurusQT thesaurus;
    thesaurus.setCaption("AiksaurusQT");
    thesaurus.hideReplacebar();
    thesaurus.doSearch("discipline");
    thesaurus.resize(330, 240);
    thesaurus.show();
    app.setMainWidget( &thesaurus );

    return app.exec();
}
