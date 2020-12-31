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

  public slots:
    void handle_textChanged(const QString &);
    void resetEveryField();
    void openQuestionFile();
    void passNext();
    void loadUserInterface();

  private:
    Ui::DialogAdmin* ui;
    QString pathToFile;
    QFile* questionFile;
    //QTextStream* fileManip;
    int section = 0;
    QVector<BoxContainer*> m_boxContainer;

    void install_default_event_handler();

    void prepareNextStep();
};

#endif // DIALOGADMIN_H
