#include "../include/LMConfigProfile.h"

LMConfigProfile::LMConfigProfile(QTabWidget* parent, int index)
        : QWidget(parent)
          , ui(new Ui::LMConfigProfile)
          , m_tabParent(parent)
          , m_index(index)
          , pr(new LMProfile(LMProfile::defaultGroupName()
                             , LMProfile::defaultGroupPicture()
                             , LMProfile::defaultPlayer1Name()
                             , LMProfile::defaultPlayer2Name()))
{
    auto* layout = new QVBoxLayout;
    layout->addWidget(pr);
    this->setLayout(layout);
    ui->setupUi(this);

    setUp_lineEdit_Added();
    setupAddedButton();
}

void LMCP::setUp_lineEdit_Added()
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

void LMCP::backupLabelValues()
{
    bkpNamesForQuickEdit.append(profile()->groupName());
    bkpNamesForQuickEdit.append(profile()->player1Name());
    bkpNamesForQuickEdit.append(profile()->player2Name());
}

void LMCP::setupAddedButton()
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
        handle_textEdited(bkpNamesForQuickEdit[0], 0);
        handle_textEdited(bkpNamesForQuickEdit[1], 1);
        handle_textEdited(bkpNamesForQuickEdit[2], 2);

        clearLineEditField();

        ui->saveBtn->setEnabled(true);
        ui->discardBtn->setEnabled(false);
    });

    connect(ui->selectPictBtn, &QPushButton::clicked, [this]() {
        auto caption = tr("Select a picture");
        auto dir = "";
        auto filter = tr("Picture") + "(*.png *.gif *.jpg)";
        picture_name = QFileDialog::getOpenFileName(this, caption, dir, filter);
        setPicture(picture_name);
    });

    connect_fieldsEditing(ui->groupNameEdit, 0);
    connect_fieldsEditing(ui->player1_Name, 1);
    connect_fieldsEditing(ui->player2_Name, 2);
}

void LMCP::clearLineEditField() const
{
    for (auto lineEdit:{ui->groupNameEdit
                        , ui->player1_Name
                        , ui->player2_Name}) { lineEdit->clear(); }
}

void LMCP::connect_fieldsEditing(QLineEdit* lineEdit, int index)
{
    connect(lineEdit, &QLineEdit::textEdited, [this, index](auto newText) {
        this->handle_textEdited(newText, index);
    });
}

void LMCP::handle_textEdited(QString const &newName, int index)
{
    if (bkpNamesForQuickEdit.isEmpty()) { backupLabelValues(); }

    if (index == 0) {
        setGroupName(newName);
    } else {
        profile()->setPlayerName(newName, index);
    }

    for (auto btn: {ui->saveBtn, ui->discardBtn}) {
        btn->setEnabled(true);
    }
}

void LMCP::setGroupName(const QString &a_name)
{
    if (a_name.isEmpty()) {
        setParentTabName(tr("Unnamed"));
        profile()->setGroupName(tr("Unnamed"));
    } else {
        setParentTabName(a_name.toUpper());
        profile()->setGroupName(a_name.toUpper());
    }
}

void LMCP::setParentTabName(QString const &a_groupName)
{
    if (m_index != -1) {
        m_tabParent->setTabText(m_index, a_groupName);
    }
}

void LMCP::setPicture(QString const &a_picture) const
{
    if (!a_picture.isEmpty()) {
        profile()->setGroupPicture(a_picture);
    }
}

LMCP::~LMConfigProfile() { delete ui; }

void LMCP::resetToDefault()
{
    clearLineEditField();
    profile()->setDefaultPicture();
    setGroupName(tr("Group %1").arg(m_index + 1));
}
