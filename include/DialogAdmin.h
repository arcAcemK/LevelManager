#ifndef DIALOGADMIN_H
#define DIALOGADMIN_H

#include <QDialog>
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include "BoxContainer.h"
#include "ConfigurePlayer.h"
#include "UserInterface.h"
#include "ui_/ui_DialogAdmin.h"
#include "LMGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class DialogAdmin;
}
QT_END_NAMESPACE

class DialogAdmin: public QDialog
{
  Q_OBJECT

  public:
    DialogAdmin(QWidget* parent = nullptr);

    ~DialogAdmin();

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
    Ui::DialogAdmin* ui;
    QString pathToQstFile;
    QFile* questionFile;
    //QTextStream* fileManip;
    QVector<BoxContainer*> m_boxContainer;

    void install_default_event_handler();

    void prepareNextStep();
    friend void LMG::setIcon(QLabel*, const QString &, QSize);
};

#endif // DIALOGADMIN_H
