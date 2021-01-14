#ifndef LMPROFILE_H
#define LMPROFILE_H

#include "ui_/ui_LMProfile.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "LMGlobal.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LMProfile;
}
QT_END_NAMESPACE

class LMProfile: public QWidget
{
  Q_OBJECT
  public:
    LMProfile(const QString &groupName = LMProfile::defaultGroupName()
              , const QString &picture = LMProfile::defaultGroupPicture()
              , const QString &namePlayer1 = LMProfile::defaultPlayer1Name()
              , const QString &namePlayer2 = LMProfile::defaultPlayer2Name()
              , QWidget* parent = nullptr);

    explicit LMProfile(const LMProfile &box, QWidget* parent = nullptr);
    ~LMProfile();

  public slots:
    void setGroupPicture(const QString &picture = "");
    void setDefaultPicture();
    void setGroupName(const QString &name);
    void setPlayer1Name(const QString &name);
    void setPlayer2Name(const QString &name);
    void changeIncrement(int increment);

  public:
    QLabel* groupLabel() const { return ui->groupName; }
    QLabel* player1Label() const { return ui->player1; }
    QLabel* player2Label() const { return ui->player2; }
    QString groupName() const { return ui->groupName->text(); }
    QString player1Name() const { return ui->player1->text(); }
    QString player2Name() const { return ui->player2->text(); }
    QString groupPicture() const { return picturePath; }
    QString reward() const;

    void setPlayerName(const QString &name, int whichPlayer);
    void setReward(int reward);
    QList<QLabel*> groupAndPlayers() const;

    /*statics*/
    static QString defaultGroupPicture() { return ":/defaultAvatar.svg"; }
    static QString defaultGroupName() { return tr("Unnamed"); }
    static QString defaultPlayer1Name() { return tr("Player1"); }
    static QString defaultPlayer2Name() { return tr("Player2"); }
  private:
    Ui::LMProfile* ui;
    QString picturePath;
    friend void LMG::set_QLabelIcon(QLabel* l, const QString &iconPath
                                    , QSize iconSize);
};

#endif // LMPROFILE_H
