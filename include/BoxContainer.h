#ifndef BOXCONTAINER_H
#define BOXCONTAINER_H

#include "ui_/ui_BoxContainer.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "LMGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class BoxContainer;
}
QT_END_NAMESPACE

class BoxContainer: public QWidget
{
  Q_OBJECT
  public slots:
    void setGroupPicture(const QString &picture = "");
    void setDefaultPicture();
    void setGroupName(const QString &name);
    void setPlayer1Name(const QString &name);
    void setPlayer2Name(const QString &name);
    void changeIncrement(int increment);

  public:
    explicit BoxContainer(const QString &groupName = ""
                          , const QString &picture = ""
                          , const QString &namePlayer1 = ""
                          , const QString &namePlayer2 = ""
                          , QWidget* parent = nullptr);

    explicit BoxContainer(BoxContainer const &box, QWidget* parent = nullptr);
    ~BoxContainer();
    QLabel* groupLabel() const;
    QLabel* player1Label() const;
    QLabel* player2Label() const;
    QString groupName() const;
    void setPlayerName(const QString &name, int whichPlayer);
    QString player1Name() const;
    QString player2Name() const;
    void setReward(int reward);
    QString reward() const;
    QList<QLabel*> playersAndGroupName() const;
    QString groupPicture() const;
    static QString defaultGroupPic();
  private:
    Ui::BoxContainer* ui;
    QString picturePath;
    friend void LMG::setIcon(QLabel*, const QString &, QSize);
};

#endif // BOXCONTAINER_H
