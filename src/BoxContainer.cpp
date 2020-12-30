#include "../include/BoxContainer.h"

BoxContainer::BoxContainer(QString groupName, QString picture
                           , QString namePlayer1, QString namePlayer2
                           , QWidget* parent)
        : QWidget(parent), ui(new Ui::BoxContainer) {
    ui->setupUi(this);
    ui->groupName->setAlignment(Qt::AlignCenter);
    ui->player1->setAlignment(Qt::AlignCenter);
    ui->player2->setAlignment(Qt::AlignCenter);
    ui->groupNote->setAlignment(Qt::AlignCenter);
    setGroupName(groupName);
    setGroupPicture(picture);
    setPlayer1Name(namePlayer1);
    setPlayer2Name(namePlayer2);
}

BoxContainer::BoxContainer(BoxContainer const &refBox, QWidget* parent)
        : QWidget(parent), ui(new Ui::BoxContainer) {
    ui->setupUi(this);
    ui->groupName->setAlignment(Qt::AlignCenter);
    ui->player1->setAlignment(Qt::AlignRight);
    ui->player2->setAlignment(Qt::AlignLeft);
    ui->groupNote->setAlignment(Qt::AlignCenter);

    setGroupName(refBox.groupName());
    setGroupPicture(refBox.pixPath);
}

void BoxContainer::setPlayer1Name(QString name) {
    if (!name.isEmpty())
        ui->player1->setText(name);
}

void BoxContainer::setPlayer2Name(QString name) {
    if (!name.isEmpty())
        ui->player2->setText(name);
}

void BoxContainer::setGroupName(QString name) {
    if (!name.isEmpty())
        ui->groupName->setText(name);
}

void BoxContainer::setGroupPicture(QString picture) {
    pix = new QPixmap(pixWidth, pixHeight);
    if (picture.isEmpty()) {
        pix->load(":/morti.gif");
        pixPath = ":/morti.gif";
    } else {
        pix->load(picture);
        pixPath = picture;
    }
    *pix = pix->scaled(pixWidth, pixHeight);
    ui->groupPicture->setPixmap(*pix);
}

void BoxContainer::setGroupPicture(QPixmap picture) {
    *pix = picture;
    ui->groupPicture->setPixmap(*pix);
    pixPath = tr("unknown");
}

void BoxContainer::setReward(int reward) {
    ui->groupNote->setText(QString::number(reward));
}

void BoxContainer::changeIncrement(int increment) {
    ui->point1->setText(QString::number(increment));
}

QString BoxContainer::reward() const { return ui->groupNote->text(); }

QString BoxContainer::groupName() const { return ui->groupName->text(); }

QPixmap BoxContainer::userPict() const { return *pix; }


BoxContainer::~BoxContainer() {
    delete ui;
}

QList<QLabel*> BoxContainer::playersAndGroupName() const {
    return QList<QLabel*>({ui->groupName, ui->player1, ui->player2});
}
