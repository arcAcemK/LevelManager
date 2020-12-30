#include "include/DialogAdmin.h"
#include "include/BoxContainer.h"
#include "include/ConfigurePlayer.h"
#include <QApplication>

int main(int argc, char* argv[])
{

    QCoreApplication::setOrganizationName(
            QTranslator::tr("Academic Research Club"));
    QCoreApplication::setApplicationName(QTranslator::tr("Level Manager"));
    QCoreApplication::setApplicationVersion("0.1f");

    QApplication app(argc, argv);

    BoxContainer b;
    //b.show();

    ConfigurePlayer c;
    //c.show();

    DialogAdmin d;
    d.show();

    BoxContainer l;
    BoxContainer e;
    BoxContainer f;
    BoxContainer g;
    QVector<BoxContainer*> lis;
    lis.append(&l);
    lis.append(&e);
    lis.append(&g);
    lis.append(&f);
    UserInterface u(lis);
    //u.show();
    return app.exec();
}
