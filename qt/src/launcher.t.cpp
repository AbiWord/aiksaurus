#include "launcher.h"
#include <qapp.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Launcher l(0, "AiksaurusQT");
    l.show();
    app.setMainWidget( &l );

    return app.exec();
}
