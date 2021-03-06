#include "../include/LMWizard.h"

LMWizard::LMWizard(QWidget* parent)
        : QDialog(parent), ui(new Ui::LMWizard), questionFile(nullptr)
{
    ui->setupUi(this);
    ui->required_label->setHidden(false);
    ui->nextBtn->setHidden(true);
    install_default_event_handler();
    auto iconSize = ui->craLabel->size() * 7;
    LMG::set_QLabelIcon(ui->craLabel, ":/cra_logo.png", iconSize);
    LMG::set_QLabelIcon(ui->acemLabel, ":/acem_logo.jpeg", iconSize);
    ui->resetBtn->setIcon(QIcon(":/reset.svg"));
    ui->cancelBtn->setIcon(QIcon(":/cancel.svg"));
}

void LMWizard::install_default_event_handler()
{
    for (auto field: {ui->organiserField, ui->competField}) {
        connect(field, &QLineEdit::textChanged, [this](
                const QString &) { emit fieldsChanged(); });
    }
    connect(ui->openFilebutton, &QToolButton::clicked, this
            , &LMWizard::get_qstFile);
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(passNext()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(resetEveryField()));
    connect(this, &LMWizard::fieldsChanged, this
            , &LMWizard::handle_fieldsChanged);
}

void LMWizard::resetEveryField()
{
    ui->organiserField->clear();
    ui->competField->clear();
    pathToQstFile.clear();
    ui->numGroupField->setValue(4);
    ui->openFilebutton->setText("...");
    emit fieldsChanged();
}

void LMWizard::handle_fieldsChanged()
{
    if ((!pathToQstFile.isEmpty()) &&
        (!ui->organiserField->text().isEmpty()) &&
        (!ui->competField->text().isEmpty())) {
        ui->resetBtn->setVisible(true);
        ui->nextBtn->setVisible(true);
        ui->required_label->setHidden(true);
    } else {
        ui->required_label->setVisible(true);
        ui->nextBtn->setHidden(true);
    }
}

void LMWizard::setFile(const QString &path_to_file)
{
    this->pathToQstFile = path_to_file;
    /* Get the base name of the file.
     Example : /home/user/file.txt --> filename = file.txt*/
    QString fileName = pathToQstFile.section("/", -1, -1);
    ui->openFilebutton->setText(fileName);
    emit fieldsChanged();
}

void LMWizard::get_qstFile()
{
    auto caption = tr("Select a file containing questions");
    auto filter = tr("File") + "(*.txt *.qst *.c *.cpp)";
    auto dir = "";
    pathToQstFile = QFileDialog::getOpenFileName(this, caption, dir, filter);
    //pathToQstFile = ":/ecriture.txt";
    questionFile = new QFile(pathToQstFile);
    if (!questionFile->exists()) {
        auto error_message = tr("File cannot be read or is corrupted!");
        QMessageBox::critical(this, tr("Error"), error_message);
    } else {
        setFile(pathToQstFile);
    }
}

void LMWizard::passNext()
{
    prepareNextStep();

    /*configureTab: Inner TabWidget*/
    auto* configureTab = new QTabWidget;
    for (int i = 0; i < ui->numGroupField->value(); ++i) {
        auto* configProfile = new LMConfigProfile(configureTab, i);
        profiles.append(configProfile->profile());
        configureTab->addTab(configProfile, "Group " + QString::number(i + 1));
    }
    configureTab->setTabPosition(QTabWidget::East);

    /*ui->tabContainer : Outer TabWidget*/
    ui->tabContainer->addTab(configureTab, tr("Configure Groups"));
    ui->tabContainer->setTabPosition(QTabWidget::South);
    setMinimumSize(0, 0);
    adjustSize();
    setMaximumSize(size());
}

void LMWizard::prepareNextStep()
{
    for (int i = 0; i < 2; ++i) {
        auto tab = ui->tabContainer->widget(0);
        ui->tabContainer->removeTab(0);
        tab->deleteLater();
    }
    delete ui->resetBtn;
    ui->nextBtn->setText(tr("Configuration &done"));
    ui->nextBtn->setDescription(tr("Main interface"));
    disconnect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(passNext()));
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(loadUserInterface()));
}

void LMWizard::loadUserInterface()
{
    auto* mainInterface = new LMMainUi(this->profiles);
    //mainInterface->setPathToFile(questionFile);
    mainInterface->setPathToFile(pathToQstFile);
    mainInterface->showFullScreen();
    done(0);
}


LMWizard::~LMWizard()
{
    delete ui;
}

