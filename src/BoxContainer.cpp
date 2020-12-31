#include "../include/BoxContainer.h"

BoxContainer::BoxContainer(QString groupName, QString picture
                           , QString namePlayer1, QString namePlayer2
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
    setGroupPicture(refBox.pixPath);
}

void BoxContainer::setPlayer1Name(QString name)
{
    if (!name.isEmpty()) {
        ui->player1->setText(name);
    }
}

void BoxContainer::setPlayer2Name(QString name)
{
    if (!name.isEmpty()) {
        ui->player2->setText(name);
    }
}

void BoxContainer::setGroupName(QString name)
{
    if (!name.isEmpty()) {
        ui->groupName->setText(name);
    }
}

void BoxContainer::setGroupPicture(QString picture)
{
    auto pixSize = ui->groupPicture->size() * 10;
    if (picture.isEmpty()) {
        pixPath = ":/defaultAvatar.svg";
        pix = (QPixmap(pixPath, "svg")
                .scaled(pixSize, Qt::KeepAspectRatio));
    } else {
        pixPath = picture;
        pix = QPixmap(picture).scaled(pixSize, Qt::KeepAspectRatio);
    }
    //*pix = pix->scaled(pixWidth, pixHeight);
    ui->groupPicture->setPixmap(pix);
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

QPixmap BoxContainer::userPict() const { return pix; }


BoxContainer::~BoxContainer() { delete ui; }

QList<QLabel*> BoxContainer::playersAndGroupName() const
{
    return QList<QLabel*>({ui->groupName, ui->player1, ui->player2});
}
