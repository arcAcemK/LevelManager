#include "../include/LMProfile.h"

LMProfile::LMProfile(const QString &groupName
                     , const QString &picture
                     , const QString &namePlayer1
                     , const QString &namePlayer2
                     , QWidget* parent)
        : QWidget(parent), ui(new Ui::LMProfile)
{
    ui->setupUi(this);
    setGroupName(groupName);
    setGroupPicture(picture);
    setPlayer1Name(namePlayer1);
    setPlayer2Name(namePlayer2);
}

LMProfile::LMProfile(LMProfile const &refBox, QWidget* parent)
        : QWidget(parent), ui(new Ui::LMProfile)
{
    ui->setupUi(this);
    setGroupName(refBox.groupName());
    setPlayer1Name(refBox.player1Name());
    setPlayer2Name(refBox.player2Name());
    setGroupPicture(refBox.groupPicture());
}

void LMProfile::setPlayerName(const QString &name, int whichPlayer)
{
    if (whichPlayer == 1) {
        setPlayer1Name(name);
    } else {
        setPlayer2Name(name);
    }
}

void LMProfile::setPlayer1Name(const QString &name)
{
    if (!name.isEmpty()) {
        ui->player1->setText(name);
    }
}

void LMProfile::setPlayer2Name(const QString &name)
{
    if (!name.isEmpty()) {
        ui->player2->setText(name);
    }
}

void LMProfile::setGroupName(const QString &name)
{
    if (!name.isEmpty()) {
        ui->groupName->setText(name);
    }
}

void LMProfile::setGroupPicture(const QString &picture)
{
    auto pixSize = ui->groupPicture->size() * 10;
    if (picture.isEmpty()) {
        picturePath = LMProfile::defaultGroupPicture();
    } else {
        picturePath = picture;
    }
    LMG::set_QLabelIcon(ui->groupPicture, picturePath, pixSize);
}

void LMProfile::setDefaultPicture() { setGroupPicture(); }

void LMProfile::setReward(int reward)
{
    ui->groupNote->setText(QString::number(reward));
}

void LMProfile::changeIncrement(int increment)
{
    ui->point1->setText(QString("%1").arg(increment));
}

QString LMProfile::reward() const { return ui->groupNote->text(); }

LMProfile::~LMProfile() { delete ui; }

QList<QLabel*> LMProfile::groupAndPlayers() const
{
    return QList<QLabel*>({ui->groupName, ui->player1, ui->player2});
}

