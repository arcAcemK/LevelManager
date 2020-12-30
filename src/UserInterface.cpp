#include "../include/UserInterface.h"

UserInterface::UserInterface(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::UserInterface) {
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget *centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    addPlayer();
    addPlayer();
    addPlayer();
    addPlayer();
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
    resize(720, 480);
}

UserInterface::UserInterface(QVector<BoxContainer *> listePlayers,
                             QWidget *parent)
        : QMainWindow(parent), ui(new Ui::UserInterface) {
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget *centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(listePlayers);
    for (int i = 0; i < m_listePlayers.size(); ++i)
        addPlayer(m_listePlayers.at(i));

    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
}

UserInterface::UserInterface(QList<BoxContainer *> listePlayers,
                             QWidget *parent)
        : QMainWindow(parent), ui(new Ui::UserInterface) {
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget *centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(listePlayers);
    for (int i = 0; i < m_listePlayers.size(); ++i)
        addPlayer(m_listePlayers.at(i));
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
}

/**
 * @brief UserInterface::UserInterface
 * @brief Construct a UserInterface by annother one give as a parametter here const & interf
 * @param interf
 * @param parent
 */
UserInterface::UserInterface(UserInterface const &interf, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::UserInterface) {
    ui->setupUi(this);
    createMenuBar();
    openQuestionFile();
    createDefaultBottomDockWidget();
    QWidget *centraleZone = new QWidget(this);
    centralHLayout = new QHBoxLayout(centraleZone);
    setListePlayers(interf.m_listePlayers);

    for (int i = 0; i < m_listePlayers.size(); ++i)
        addPlayer(m_listePlayers.at(i));
    centraleZone->setLayout(centralHLayout);
    setCentralWidget(centraleZone);
    //resize(720,480);
}

void UserInterface::createMenuBar() {
    QAction *openFullScreen = new QAction(tr("&Open Full screen"));
    QAction *exitFullScreen = new QAction(tr("&Exit full screen"));
    QAction *exit = new QAction(tr("E&xit"));
    QAction *about = new QAction(tr("&About"));
    QAction *credit = new QAction(tr("&Credits"));
    QAction *aboutQt = new QAction(tr("About &Qt5.14.1"));
    QMenu *tools = ui->menubar->addMenu(tr("&Tools"));
    tools->addAction(openFullScreen);
    tools->addAction(exitFullScreen);
    tools->addAction(exit);
    connect(openFullScreen, SIGNAL(triggered()), this, SLOT(showFullScreen()));
    connect(exitFullScreen, SIGNAL(triggered()), this, SLOT(showMaximized()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    openFullScreen->setShortcut(QKeySequence::FullScreen);
    exitFullScreen->setShortcut(QKeySequence::Cancel);
    exit->setShortcut(QKeySequence(tr("CTRL+Q")));
    connect(new QShortcut(QKeySequence("CTRL+W"), this),
            SIGNAL(activated()), this, SLOT(close()));
    QMenu *help = ui->menubar/*menuBar()*/->addMenu(tr("&Help"));
    help->addAction(about);
    help->addAction(credit);
    help->addAction(aboutQt);
    connect(about, SIGNAL(triggered()), this, SLOT(openAbout()));
    connect(credit, SIGNAL(triggered()), this, SLOT(openCredit()));
    connect(aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(new QShortcut(QKeySequence("ALT+0"), this),
            SIGNAL(activated()), this, SLOT(hideMenuBar()));
    /*
    */
}

void UserInterface::openQuestionFile() {

    /*pathToFile = QFileDialog::getOpenFileName(this,tr("Choose question's file to load"),
                                              "",tr("File")+"(*.txt *.qst *.c *.cpp)");
                                              */
    pathToFile = ":/ecriture.txt";
    questionFile = new QFile(pathToFile);
    questionFile->open(QIODevice::ReadOnly);

    fileManip = new QTextStream(questionFile);
    fileManip->setCodec("UTF-8");

    QString line;
    while (!(line = fileManip->readLine()).isNull())
        listeOfQuestions.append(line);

    m_answer = listeOfQuestions.at(0).section(':', -1);
    m_currentQuestion = listeOfQuestions.at(0).section(':', 0, 0);
    currentIndex = 0;
    delete fileManip;
    delete questionFile;
    // fileManip.setCodec();
    // QMessageBox::information(this,"Fichier",fileManip.readLine());
}

void UserInterface::createDefaultBottomDockWidget() {
    QDockWidget *dockWidget = new QDockWidget(this);
    QWidget *mainWidget = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QPushButton *next = new QPushButton(tr("Next"));
    questionField = new QLineEdit(m_currentQuestion);
    QPushButton *prev = new QPushButton(tr("Previous"));
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

void UserInterface::prevQuestion() {
    if (currentIndex > 0) {
        QString question = listeOfQuestions.at(--currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        questionField->setText(m_currentQuestion);
    }
}

void UserInterface::nextQuestion() {
    if (currentIndex < listeOfQuestions.size() - 1) {
        QString question = listeOfQuestions.at(++currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        questionField->setText(m_currentQuestion);
    }
}

void UserInterface::openAbout() {
    QString message = m_competitionName
                      + tr(" is a competition organised by ")
                      + m_OrgansationName
                      + ".";
    if (!m_about.isEmpty())
        message += tr(" It consist to ") + m_about;
    QMessageBox::question(this, "About", message);
}

void UserInterface::openCredit() {
    QMessageBox::question(this, tr("Credit"), tr("Level Manager is a free software edited by \
                 Faouzi Mohamed"), QMessageBox::Ok);
}

void UserInterface::setListePlayers(QList<BoxContainer *> liste) {
    for (int i = 0; i < liste.size(); ++i)
        m_listePlayers.append(new BoxContainer(*(liste.at(i)), this));
}

void UserInterface::setListePlayers(QVector<BoxContainer *> liste) {
    for (int i = 0; i < liste.size(); ++i)
        m_listePlayers.append(new BoxContainer(*(liste.at(i))));
}

QVector<BoxContainer *> UserInterface::listePlayers() { return m_listePlayers; }

void UserInterface::setPathToFile(QString const &path) {
    if (path.isEmpty())
        pathToFile = "../LevelManager/ecriture.txt";
    else pathToFile = QString(path);
}


void UserInterface::setPathToFile(QFile *file) {
    if (questionFile == nullptr) {
        questionFile = new QFile(file->fileName());
    } else {
        delete questionFile;
        questionFile = new QFile(file->fileName());
    }
    pathToFile = questionFile->fileName();
}

QString UserInterface::currentQuestion() { return m_currentQuestion; }

void UserInterface::addPlayer(BoxContainer *player) {
    if (player == nullptr)
        player = new BoxContainer(tr("No_Named"), tr(""), tr("Player1"),
                                  tr("Player2"), this);
    //player->setParent(this);
    centralHLayout->addWidget(player);
}

void UserInterface::setAbout(QString about) { m_about = about; }

void
UserInterface::setCompetitionName(QString name) { m_competitionName = name; }

void
UserInterface::setOrganisationName(QString name) { m_OrgansationName = name; }

void UserInterface::hideMenuBar() {
    if (ui->menubar->isHidden())
        ui->menubar->setVisible(true);
    else
        ui->menubar->setHidden(true);
}

UserInterface::~UserInterface() {
    delete ui;
}

