#ifndef LMWIZZARD_H
#define LMWIZZARD_H

#include <QDialog>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "LMProfile.h"
#include "LMConfigProfile.h"
#include "LMMainUi.h"
#include "ui_/ui_LMWizzard.h"
#include "LMGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LMWizzard;
}
QT_END_NAMESPACE

class LMWizzard: public QDialog
{
  Q_OBJECT

  public:
    LMWizzard(QWidget* parent = nullptr);

    ~LMWizzard();

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
    Ui::LMWizzard* ui;
    QString pathToQstFile;
    QFile* questionFile;
    //QTextStream* fileManip;
    QVector<LMProfile*> m_boxContainer;

    void install_default_event_handler();

    void prepareNextStep();
    friend void LMG::setIcon(QLabel*, const QString &, QSize);
};

#endif // LMWIZZARD_H
