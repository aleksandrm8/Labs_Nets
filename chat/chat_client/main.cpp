#include "dialog.h"
#include <QApplication>
#include <QTranslator>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    QTranslator translator;
    translator.load( "chat_client_" + QLocale::system().name() );
    app.installTranslator( &translator );
    Dialog w;
    w.show();
    return app.exec();
}
