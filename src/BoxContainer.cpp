#include "../include/BoxContainer.h"

BoxContainer::BoxContainer(const QString &groupName
                           , const QString &picture
                           , const QString &namePlayer1
                           , const QString &namePlayer2
                           , QWidget* parent)
        : QWidget(parent), ui(new Ui::BoxContainer)
{
    ui->setupUi(this);
    setGroupName(groupName);
    setGroupPicture(picture);
    setPlayer1Name(namePlayer1);
    setPlayer2Name(namePlayer2);
}

BoxContainer::BoxContainer(BoxContainer const &refBox, QWidget* parent)
        : QWidget(parent), ui(new Ui::BoxContainer)
{
    ui->setupUi(this);
    setGroupName(refBox.groupName());
    setPlayer1Name(refBox.player1Name());
    setPlayer2Name(refBox.player2Name());
    setGroupPicture(refBox.groupPicture());
}

void BoxContainer::setPlayerName(const QString &name, int whichPlayer)
{
    if (whichPlayer == 1) {
        setPlayer1Name(name);
    } else {
        setPlayer2Name(name);
    }
}

void BoxContainer::setPlayer1Name(const QString &name)
{
    if (!name.isEmpty()) {
        ui->player1->setText(name);
    }
}

void BoxContainer::setPlayer2Name(const QString &name)
{
    if (!name.isEmpty()) {
        ui->player2->setText(name);
    }
}

void BoxContainer::setGroupName(const QString &name)
{
    if (!name.isEmpty()) {
        ui->groupName->setText(name);
    }
}

void BoxContainer::setGroupPicture(const QString &picture)
{
    auto pixSize = ui->groupPicture->size() * 10;
    if (picture.isEmpty()) {
        picturePath = BoxContainer::defaultGroupPic();
    } else {
        picturePath = picture;
    }
    LMG::setIcon(ui->groupPicture, picturePath, pixSize);
}

void BoxContainer::setDefaultPicture() { setGroupPicture(); }

void BoxContainer::setReward(int reward)
{
    ui->groupNote->setText(QString::number(reward));
}

void BoxContainer::changeIncrement(int increment)
{
    ui->point1->setText(QString("%1").arg(increment));
}

QString BoxContainer::reward() const { return ui->groupNote->text(); }

QString BoxContainer::groupName() const { return ui->groupName->text(); }

QString BoxContainer::player1Name() const { return ui->player1->text(); }

QString BoxContainer::player2Name() const { return ui->player2->text(); }

QLabel* BoxContainer::groupLabel() const { return ui->groupName; }

QLabel* BoxContainer::player1Label() const { return ui->player1; }

QLabel* BoxContainer::player2Label() const { return ui->player2; }

QString BoxContainer::groupPicture() const { return picturePath; }

BoxContainer::~BoxContainer() { delete ui; }

QList<QLabel*> BoxContainer::playersAndGroupName() const
{
    return QList<QLabel*>({ui->groupName, ui->player1, ui->player2});
}

QString BoxContainer::defaultGroupPic() { return ":/defaultAvatar.svg"; }
