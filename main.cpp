#include "include/LMWizzard.h"
#include "include/LMProfile.h"
#include "include/LMConfigProfile.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QCoreApplication::setOrganizationName(
            QTranslator::tr("Academic Research Club"));
    QCoreApplication::setApplicationName(QTranslator::tr("Level Manager"));
    QCoreApplication::setApplicationVersion("0.1f");

    QApplication app(argc, argv);

    LMProfile b;
    //b.show();

    LMConfigProfile c;
    //c.show();

    LMWizzard d;
    //d.show();

    LMProfile l;
    LMProfile e;
    LMProfile f;
    LMProfile g;
    QList<LMProfile*> lis;
    lis.append(&l);
    lis.append(&e);
    lis.append(&g);
    lis.append(&f);
    LMMainUi u(lis);
    u.show();
    return app.exec();
}
