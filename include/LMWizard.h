#ifndef LMWIZARD_H
#define LMWIZARD_H

#include <QDialog>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "LMProfile.h"
#include "LMConfigProfile.h"
#include "LMMainUi.h"
#include "ui_/ui_LMWizard.h"
#include "LMGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LMWizard;
}
QT_END_NAMESPACE

class LMWizard: public QDialog
{
  Q_OBJECT

  public:
    LMWizard(QWidget* parent = nullptr);

    ~LMWizard();

  signals:
    /*Signal emitted whenever a field is edited*/
    void fieldsChanged();

  public slots:
    void handle_fieldsChanged();
    void resetEveryField();
    void setFile(const QString &path_to_file);
    void get_qstFile();
    void passNext();
    void loadUserInterface();

  private:
    Ui::LMWizard* ui;
    QString pathToQstFile;
    QFile* questionFile;
    //QTextStream* fileManip;
    QList<LMProfile*> profiles;

    void install_default_event_handler();

    void prepareNextStep();
    friend void LMG::set_QLabelIcon(QLabel* l, const QString &iconPath
                                    , QSize iconSize);
};

#endif // LMWIZARD_H
