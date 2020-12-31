#include "../include/ConfigurePlayer.h"

ConfigurePlayer::ConfigurePlayer(QTabWidget* parent, int index)
        : QWidget(parent), ui(new Ui::ConfigurePlayer), m_tabParent(parent),
          m_index(index)
{
    bx = new BoxContainer(tr("Unnamed"), tr(""), tr("Player1"), tr("Player2"));
    auto* layout = new QVBoxLayout;
    layout->addWidget(bx);
    this->setLayout(layout);
    ui->setupUi(this);

    setUp_lineEdit_Added();
    setupAddedButton();
}

void ConfigurePlayer::setUp_lineEdit_Added()
{
    /** Example of Match  : "A", "ACEM", "A CE- M",... */
    QRegExp regexGroup(R"(^\S(\s?\S)*)");
    auto groupValidator = new QRegExpValidator(regexGroup, this);
    ui->groupNameEdit->setValidator(groupValidator);

    /** Example of Match : "A", [:whitespace:], " A", "ACEM", "A CE- M", ...*/
    QRegExp regexPlayers(R"(^\s?(\S\s?)*)");
    auto playerValidator = new QRegExpValidator(regexPlayers, this);    
    ui->player1_Name->setValidator(playerValidator);
    ui->player2_Name->setValidator(playerValidator);
}

void ConfigurePlayer::backupLabelValues()
{
    auto playersAndGroupName = bx->playersAndGroupName();
    bkpNamesForQuickEdit.append(playersAndGroupName[0]->text());
    bkpNamesForQuickEdit.append(playersAndGroupName[1]->text());
    bkpNamesForQuickEdit.append(playersAndGroupName[2]->text());
}

void ConfigurePlayer::setupAddedButton()
{
    ui->selectPictBtn->setCursor(Qt::PointingHandCursor);
    ui->discardBtn->setIcon(QIcon(":/discard.svg"));
    ui->saveBtn->setIcon(QIcon(":/save.svg"));
    ui->selectPictBtn->setIcon(QIcon(":/picture.svg"));
    ui->resetButton->setIcon(QIcon(":/reset.svg"));
    for (QPushButton* btn: {ui->saveBtn, ui->discardBtn}) {
        btn->setCursor(Qt::PointingHandCursor);
    }

    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetToDefault()));

    connect(ui->saveBtn, &QPushButton::clicked, [this]() {
        ui->saveBtn->setEnabled(false);
        ui->discardBtn->setEnabled(false);
        clearLineEditField();         //Clear saved values and
        bkpNamesForQuickEdit.clear();//Remove old saved values from the list and
        backupLabelValues();        //Save new values temporary in memory 
    });

    connect(ui->discardBtn, &QPushButton::clicked, [this]() {
        auto playersAndGroupName = bx->playersAndGroupName();
        handle_textEdited(bkpNamesForQuickEdit[0], 0);
        handle_textEdited(bkpNamesForQuickEdit[1], 1);
        handle_textEdited(bkpNamesForQuickEdit[2], 2);

        clearLineEditField();

        ui->saveBtn->setEnabled(true);
        ui->discardBtn->setEnabled(false);
    });

    connect(ui->selectPictBtn, &QPushButton::clicked,
            [this]() {
                pathToPic = (
                        QFileDialog::getOpenFileName(this,
                                                     tr("Select a picture"),
                                                     "",
                                                     tr("Picture") +
                                                     "(*.png *.gif *.jpg)"));
                setPicture(pathToPic);
            });

    connect_fieldsEditing(ui->groupNameEdit, 0);
    connect_fieldsEditing(ui->player1_Name, 1);
    connect_fieldsEditing(ui->player2_Name, 2);
}

void ConfigurePlayer::clearLineEditField() const
{
    for (auto lineEdit:
            {ui->groupNameEdit,
             ui->player1_Name,
             ui->player2_Name}
            ) { lineEdit->clear(); }
}

void ConfigurePlayer::connect_fieldsEditing(QLineEdit* lineEdit, int index)
{
    connect(lineEdit, &QLineEdit::textEdited, [this, index](auto newText) {
        this->handle_textEdited(newText, index);
    });
}

void ConfigurePlayer::handle_textEdited(QString const &newName, int index)
{
    auto playersAndGroupName = boxContainer()->playersAndGroupName();
    if (bkpNamesForQuickEdit.isEmpty()) {
        backupLabelValues();
    }

    (index == 0) ? setGroupName(newName, playersAndGroupName[index])
                 : playersAndGroupName[index]->setText(newName);

    for (auto btn: {ui->saveBtn, ui->discardBtn}) {
        btn->setEnabled(true);
    }
}

void ConfigurePlayer::setGroupName(const QString &a_name, QLabel* groupLabel)
{
    if (a_name.isEmpty()) {
        setParentTabName(tr("Unnamed"));
        groupLabel->setText(tr("Unnamed"));
    } else {
        setParentTabName(a_name);
        groupLabel->setText(a_name);
    }
}

void ConfigurePlayer::setParentTabName(QString const &a_groupName)
{
    if (m_index != -1) {
        m_tabParent->setTabText(m_index, a_groupName);
    }
}

void ConfigurePlayer::setPicture(QString const &a_picture)
{
    if (!a_picture.isEmpty()) {
        boxContainer()->setGroupPicture(a_picture);
    }
}

BoxContainer* ConfigurePlayer::boxContainer() { return bx; }

ConfigurePlayer::~ConfigurePlayer() { delete ui; }

void ConfigurePlayer::resetToDefault()
{
    clearLineEditField();
    auto playersAndGroupName = boxContainer()->playersAndGroupName();
    boxContainer()->setDefaultPicture();
    setGroupName(tr("Group %1").arg(m_index + 1), playersAndGroupName[0]);
}
