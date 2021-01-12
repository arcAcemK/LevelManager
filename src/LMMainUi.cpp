#include "../include/LMMainUi.h"

LMMainUi::LMMainUi(QWidget* parent)
        : QMainWindow(parent),
          ui(new Ui::LMMainUi)
{
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    auto* centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    addPlayer();
    addPlayer();
    addPlayer();
    addPlayer();
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
    resize(720, 480);
}

LMMainUi::LMMainUi(QVector<LMProfile*> listePlayers
                   , QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LMMainUi)
{
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget* centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(listePlayers);
    for (int i = 0; i < m_listePlayers.size(); ++i) {
        addPlayer(m_listePlayers.at(i));
    }

    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
}

LMMainUi::LMMainUi(QList<LMProfile*> listePlayers, QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LMMainUi)
{
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget* centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(listePlayers);
    for (int i = 0; i < m_listePlayers.size(); ++i) {
        addPlayer(m_listePlayers.at(i));
    }
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
}

/**
 * @brief UserInterface::UserInterface
 * @brief Construct a UserInterface by annother one give as a parametter here const & interf
 * @param interf
 * @param parent
 */
LMMainUi::LMMainUi(LMMainUi const &interf, QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LMMainUi)
{
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget* centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(interf.m_listePlayers);

    for (int i = 0; i < m_listePlayers.size(); ++i) {
        addPlayer(m_listePlayers.at(i));
    }
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
    //resize(720,480);
}

void LMMainUi::createMenuBar()
{
    handle_triggeredSignal(ui->action_fullscreen, &Interface::toggleFullscreen);
    handle_triggeredSignal(ui->action_Exit, &Interface::quit);
    ui->action_Exit->setShortcut(QKeySequence(tr("CTRL+Q")));

    auto ctrl_w_seq = new QShortcut(QKeySequence("CTRL+W"), this);
    connect(ctrl_w_seq, &QShortcut::activated, this, &Interface::close);

    handle_triggeredSignal(ui->action_About, &Interface::openAbout);
    handle_triggeredSignal(ui->action_Credits, &Interface::openCredit);
    auto ctrl_h_seq = new QShortcut(QKeySequence("CTRL+H"), this);
    connect(ctrl_h_seq, SIGNAL(activated()), this, SLOT(hideMenuBar()));
}

void Interface::handle_triggeredSignal(QAction* a, VoidHandler handler) const
{
    connect(a, &QAction::triggered, this, handler);
}

void Interface::toggleFullscreen()
{
    if (isFullScreen()) {
        showNormal();
        ui->action_fullscreen->setText(tr("Enter &fullscreen"));
        ui->action_fullscreen->setShortcut(QKeySequence::FullScreen);
    } else {
        showFullScreen();
        ui->action_fullscreen->setText(tr("Exit &fullscreen"));
        ui->action_fullscreen->setShortcut(QKeySequence::Cancel);
    }
}


void LMMainUi::openQuestionFile()
{

    /*pathToFile = QFileDialog::getOpenFileName(this,tr("Choose question's file to load"),
                                              "",tr("File")+"(*.txt *.qst *.c *.cpp)");
                                              */
    pathToFile = ":/ecriture.txt";
    questionFile = new QFile(pathToFile);
    questionFile->open(QIODevice::ReadOnly);

    fileManip = new QTextStream(questionFile);
    fileManip->setCodec("UTF-8");

    QString line;
    while (!(line = fileManip->readLine()).isNull()) {
        listeOfQuestions.append(line);
    }

    m_answer = listeOfQuestions.at(0).section(':', -1);
    m_currentQuestion = listeOfQuestions.at(0).section(':', 0, 0);
    currentIndex = 0;
    delete fileManip;
    delete questionFile;
    // fileManip.setCodec();
    // QMessageBox::information(this,"Fichier",fileManip.readLine());
}

void LMMainUi::createDefaultBottomDockWidget()
{
    QDockWidget* dockWidget = new QDockWidget(this);
    QWidget* mainWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout;
    QPushButton* next = new QPushButton(tr("Next"));
    questionField = new QLineEdit(m_currentQuestion);
    QPushButton* prev = new QPushButton(tr("Previous"));
    questionField->setReadOnly(true);
    questionField->setStyleSheet("text-align:center");
    mainLayout->addWidget(prev);
    mainLayout->addWidget(questionField);
    mainLayout->addWidget(next);
    mainWidget->setLayout(mainLayout);
    dockWidget->setWidget(mainWidget);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    dockWidget->setFont(QFont("Source Code Pro"));
    this->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);

    connect(prev, SIGNAL(clicked()), this, SLOT(prevQuestion()));
    connect(next, SIGNAL(clicked()), this, SLOT(nextQuestion()));
}

void LMMainUi::prevQuestion()
{
    if (currentIndex > 0) {
        QString question = listeOfQuestions.at(--currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        questionField->setText(m_currentQuestion);
    }
}

void LMMainUi::nextQuestion()
{
    if (currentIndex < listeOfQuestions.size() - 1) {
        QString question = listeOfQuestions.at(++currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        questionField->setText(m_currentQuestion);
    }
}

void LMMainUi::openAbout()
{
    QString message = m_competitionName
                      + tr(" is a competition organised by ")
                      + m_OrgansationName
                      + ".";
    if (!m_about.isEmpty()) {
        message += tr(" It consist to ") + m_about;
    }
    QMessageBox::question(this, "About", message);
}

void LMMainUi::openCredit()
{
    QMessageBox::question(this, tr("Credit"), tr("Level Manager is a free software edited by \
                 Faouzi Mohamed"), QMessageBox::Ok);
}

void LMMainUi::setListePlayers(QList<LMProfile*> liste)
{
    for (int i = 0; i < liste.size(); ++i) {
        m_listePlayers.append(new LMProfile(*(liste.at(i)), this));
    }
}

void LMMainUi::setListePlayers(QVector<LMProfile*> liste)
{
    for (int i = 0; i < liste.size(); ++i) {
        m_listePlayers.append(new LMProfile(*(liste.at(i))));
    }
}

QVector<LMProfile*> LMMainUi::listePlayers() { return m_listePlayers; }

void LMMainUi::setPathToFile(QString const &path)
{
    if (path.isEmpty()) {
        pathToFile = "../LevelManager/ecriture.txt";
    } else { pathToFile = QString(path); }
}


void LMMainUi::setPathToFile(QFile* file)
{
    if (questionFile == nullptr) {
        questionFile = new QFile(file->fileName());
    } else {
        delete questionFile;
        questionFile = new QFile(file->fileName());
    }
    pathToFile = questionFile->fileName();
}

QString LMMainUi::currentQuestion() { return m_currentQuestion; }

void LMMainUi::addPlayer(LMProfile* player)
{
    if (player == nullptr) {
        player = new LMProfile(tr("No_Named"), tr(""), tr("Player1"),
                               tr("Player2"), this);
    }
    //player->setParent(this);
    centralHLayout->addWidget(player);
}

void LMMainUi::setAbout(QString about) { m_about = about; }

void
LMMainUi::setCompetitionName(QString name) { m_competitionName = name; }

void
LMMainUi::setOrganisationName(QString name) { m_OrgansationName = name; }

void LMMainUi::hideMenuBar()
{
    if (ui->menubar->isHidden()) {
        ui->menubar->setVisible(true);
    } else {
        ui->menubar->setHidden(true);
    }
}

LMMainUi::~LMMainUi()
{
    delete ui;
}

