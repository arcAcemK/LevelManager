#include "../include/DialogAdmin.h"

DialogAdmin::DialogAdmin(QWidget* parent)
        : QDialog(parent), ui(new Ui::DialogAdmin) {
    ui->setupUi(this);
    ui->required_label->setHidden(false);
    ui->nextBtn->setHidden(true);
    install_default_event_handler();

    int icon_size = 200;
    QPixmap craLogo = QPixmap();
    craLogo.load(":/cra_logo.png");
    craLogo = craLogo.scaled(icon_size, icon_size);
    ui->craLabel->setPixmap(craLogo);

    QPixmap acemLogo = QPixmap();
    acemLogo.load(":/acem_logo.jpeg");
    acemLogo = acemLogo.scaled(icon_size, icon_size);
    ui->acemLabel->setPixmap(acemLogo);
}

void DialogAdmin::install_default_event_handler() {
    connect(ui->organiserField, &QLineEdit::textChanged, this,
            &DialogAdmin::handle_textChanged);
    connect(ui->competField, &QLineEdit::textChanged, this,
            &DialogAdmin::handle_textChanged);
    connect(ui->openFilebutton, &QToolButton::clicked, this,
            &DialogAdmin::openQuestionFile);
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(passNext()));
    connect(ui->resetBtn, &QPushButton::clicked, this,
            &DialogAdmin::resetEveryField);
}

void DialogAdmin::handle_textChanged(const QString &) {
    if (
            (!ui->organiserField->text().isEmpty()) &&
            (!ui->competField->text().isEmpty()) &&
            (!pathToFile.isEmpty())
            ) {
        ui->resetBtn->setVisible(true);
        ui->nextBtn->setVisible(true);
        ui->required_label->setHidden(true);
    } else {
        ui->required_label->setVisible(true);
        ui->resetBtn->setHidden(true);
        ui->nextBtn->setHidden(true);
    }
}

void DialogAdmin::resetEveryField() {
    ui->organiserField->clear();
    ui->competField->clear();
    ui->numGroupField->setValue(4);
    ui->nextBtn->setHidden(true);
    pathToFile.clear();
}

void DialogAdmin::openQuestionFile() {
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
#ifdef linux
    pathToFile = QFileDialog::getOpenFileName(this,
                                              tr("Choose question's file to load"),
                                              "", tr("File") +
                                                  "(*.txt *.qst *.c *.cpp)");
#else
    pathToFile = QFileDialog::getOpenFileName(this,tr("Choose question's file to load"),
                                              /*name*/"",tr("File")+"(*.txt *.qst *.c *.cpp)");
#endif

    //pathToFile = ":/ecriture.txt";
    questionFile = new QFile(pathToFile);
    if (!questionFile->open(QIODevice::ReadOnly))
        QMessageBox::critical(this, tr("Error"), tr("File not founded"));
    else {
        questionFile->close();
        QString fileName = pathToFile.section("/", -1, -1);
        ui->openFilebutton->setText(fileName);
        if ((!ui->organiserField->text().isEmpty()) &&
            (!ui->competField->text().isEmpty())) {
            ui->resetBtn->setVisible(true);
            ui->nextBtn->setVisible(true);
            ui->required_label->setHidden(true);
        }
    }

}

void DialogAdmin::passNext() {
    prepareNextStep();

    /*configureTab: Inner TabWidget*/
    auto* configureTab = new QTabWidget;
    for (int i = 0; i < ui->numGroupField->value(); ++i) {
        auto* group = new ConfigurePlayer(configureTab, i);
        m_boxContainer.append(group->boxContainer());
        configureTab->addTab(group, "Group " + QString::number(i + 1));
    }
    configureTab->setTabPosition(QTabWidget::East);

    /*ui->tabContainer : Outer TabWidget*/
    ui->tabContainer->addTab(configureTab, tr("Configure Groups"));
    ui->tabContainer->setTabPosition(QTabWidget::South);
    setMinimumSize(0, 0);
    adjustSize();
    setMaximumSize(size());
}

void DialogAdmin::prepareNextStep() {
    for (int i = 0; i < 2; ++i) {
        auto tab = ui->tabContainer->widget(0);
        ui->tabContainer->removeTab(0);
        tab->deleteLater();
    }
    delete ui->resetBtn;
    ui->nextBtn->setText(tr("&Finish"));
    disconnect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(passNext()));
    connect(ui->nextBtn, SIGNAL(clicked()), this, SLOT(loadUserInterface()));
}

void DialogAdmin::loadUserInterface() {
    auto* mainInterface = new UserInterface(this->m_boxContainer);
    //mainInterface->setPathToFile(questionFile);
    mainInterface->setPathToFile(pathToFile);
    mainInterface->showFullScreen();
    done(0);
}


DialogAdmin::~DialogAdmin() {
    delete ui;
}

