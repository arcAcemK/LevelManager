#include "../include/LMMainUi.h"

LMMainUi::LMMainUi(QWidget* parent)
        : QMainWindow(parent)
          , ui(new Ui::LMMainUi)
          , m_competitionName(QString("This"))
          , m_OrganisationName(QCoreApplication::organizationName())
          , currentIndex(-1)
{
    ui->setupUi(this);
    setup_menuBar_event();
    open_questionFile();
    setup_questionsFields();
}

LMMainUi::LMMainUi(const QList<LMProfile*> &profiles, QWidget* parent)
        : LMMainUi(parent)
{
    setProfilesList(profiles);
    for (auto groupProfile: m_profilesList) {
        addGroupProfile(groupProfile);
    }
}

LMMainUi::LMMainUi(LMMainUi &main_ui, QWidget* parent)
        : LMMainUi(main_ui.profilesList(), parent) {}

void LMMainUi::setup_menuBar_event()
{
    /*These four connections work only if the menuBar is visible*/
    //For the Tools Menu
    handle_triggeredSignal(ui->action_fullscreen, &LMMainUi::toggle_fullscreen);
    handle_triggeredSignal(ui->action_Exit, &LMMainUi::quit);

    //For the Help Menu
    handle_triggeredSignal(ui->action_About, &LMMainUi::openAbout);
    handle_triggeredSignal(ui->action_Credits, &LMMainUi::openCredit);

    //Some useful shortcut
    auto ctrl_q = Qt::Key(Qt::CTRL + Qt::Key_Q);
    auto ctrl_h = Qt::Key(Qt::CTRL + Qt::Key_H);
    LMG::set_QActionShortcut(ui->action_Exit, ctrl_q);
    handle_sequenceKey_shortcut(ctrl_q, &LMMainUi::quit);
    handle_sequenceKey_shortcut(ctrl_h, &LMMainUi::toggle_menuBar_visibility);
    handle_sequenceKey_shortcut(Qt::Key_F11, &LMMainUi::toggle_fullscreen);
}


void LMMainUi::handle_sequenceKey_shortcut(Qt::Key seq, VoidHandler handler)
{
    auto shortcut = new QShortcut(seq, this);
    connect(shortcut, &QShortcut::activated, this, handler);
    connect(shortcut, &QShortcut::activatedAmbiguously, this, handler);

}

void LMMainUi::handle_triggeredSignal(QAction* a, VoidHandler handler) const
{
    connect(a, &QAction::triggered, this, handler);
}

void LMMainUi::toggle_fullscreen()
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

void LMMainUi::open_questionFile()
{
    /*pathToFile = QFileDialog::getOpenFileName(this,tr("Choose question's file to load"),
                                              "",tr("File")+"(*.txt *.qst *.c *.cpp)");
                                              */
    pathToFile = LMMainUi::defaultQstFile();
    QFile data(pathToFile);
    data.open(QIODevice::ReadOnly);

    QTextStream questions_answers(&data);
    questions_answers.setCodec("UTF-8");

    QString line;
    while (!(line = questions_answers.readLine()).isNull()) {
        questionList.append(line);
    }

    m_answer = questionList.at(0).section(':', -1);
    m_currentQuestion = questionList.at(0).section(':', 0, 0);
    currentIndex = 0;
}

void LMMainUi::toggle_menuBar_visibility()
{
    ui->menubar->setVisible(ui->menubar->isHidden());
}

void LMMainUi::setup_questionsFields()
{
    ui->questionField->setText(currentQuestion());
    connect(ui->prev, SIGNAL(clicked()), this, SLOT(prevQuestion()));
    connect(ui->next, SIGNAL(clicked()), this, SLOT(nextQuestion()));
}

void LMMainUi::prevQuestion()
{
    if (currentIndex > 0) {
        QString question = questionList.at(--currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        ui->questionField->setText(m_currentQuestion);
    }
}

void LMMainUi::nextQuestion()
{
    if (currentIndex < questionList.size() - 1) {
        QString question = questionList.at(++currentIndex);
        m_answer = question.section(':', -1);
        m_currentQuestion = question.section(':', 0, 0);
        ui->questionField->setText(m_currentQuestion);
    }
}

void LMMainUi::openAbout()
{
    QString message("");
    message += m_competitionName;
    message += tr(" is a competition organised by ");
    message += m_OrganisationName;
    message += ".";;

    if (!m_about.isEmpty()) {
        message += tr(" It consist to ") + m_about;
    }
    QMessageBox::question(this, "About", message);
}

void LMMainUi::openCredit()
{
    auto title = tr("Credit");
    QString message("");
    message += QCoreApplication::applicationName();
    message += tr(" is a free software edited by ");
    message += QCoreApplication::organizationName();
    QMessageBox::information(this, title, message, QMessageBox::Ok);
}

void LMMainUi::setProfilesList(const QList<LMProfile*> &list)
{
    for (auto profile :list) {
        m_profilesList.append(new LMProfile(*profile, this));
    }
}

const QList<LMProfile*> &LMMainUi::profilesList() { return m_profilesList; }

void LMMainUi::setPathToFile(const QString &path)
{
    pathToFile = path.isEmpty()? LMMainUi::defaultQstFile() : path;
}

const QString &LMMainUi::currentQuestion() { return m_currentQuestion; }

void LMMainUi::addGroupProfile(LMProfile* a_profile)
{
    if (a_profile == nullptr) {
        a_profile = new LMProfile(LMProfile::defaultGroupName()
                                  , LMProfile::defaultGroupPicture()
                                  , LMProfile::defaultPlayer1Name()
                                  , LMProfile::defaultPlayer2Name(), this);
    }
    auto centralWidget = ui->widget;
    auto centralHLayout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    centralHLayout->addWidget(a_profile);
}

void LMMainUi::setAbout(const QString &about) { m_about = about; }

void LMMainUi::setCompetitionName(const QString &name)
{
    m_competitionName = name;
}

void LMMainUi::setOrganisationName(const QString &name)
{
    m_OrganisationName = name;
}


LMMainUi::~LMMainUi()
{
    delete ui;
}

