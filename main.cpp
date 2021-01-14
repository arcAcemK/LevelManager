#include "include/LMWizard.h"
#include "include/LMProfile.h"
#include "include/LMConfigProfile.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    auto org_name = QTranslator::tr("Academic Research Club of Kenitra");
    auto app_name = QTranslator::tr("Level Manager");
    auto app_version = QTranslator::tr("0.1f");
    QCoreApplication::setOrganizationName(org_name);
    QCoreApplication::setApplicationName(app_name);
    QCoreApplication::setApplicationVersion(app_version);

    QApplication app(argc, argv);

    LMProfile b;
    //b.show();

    LMConfigProfile c;
    //c.show();

    LMWizard d;
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
