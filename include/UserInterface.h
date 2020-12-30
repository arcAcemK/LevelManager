#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QMainWindow>
#include "BoxContainer.h"
#include "ui_/ui_UserInterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserInterface; }
QT_END_NAMESPACE

class UserInterface : public QMainWindow {
Q_OBJECT
public slots:

    void openAbout();

    void openCredit();

    void prevQuestion();

    void nextQuestion();

    void hideMenuBar();

public:
    explicit UserInterface(QWidget *parent = nullptr);

    explicit UserInterface(QList<BoxContainer *> listePlayers,
                           QWidget *parent = nullptr);

    explicit UserInterface(QVector<BoxContainer *> listePlayers,
                           QWidget *parent = nullptr);

    explicit UserInterface(UserInterface const &interf,
                           QWidget *parent = nullptr);

    ~UserInterface();

    void addPlayer(BoxContainer *player = nullptr);

    void setListePlayers(QList<BoxContainer *> liste);

    void setListePlayers(QVector<BoxContainer *> liste);

    void setAbout(QString);

    void setCompetitionName(QString);

    void setOrganisationName(QString);

    QString currentQuestion();

    QVector<BoxContainer *> listePlayers();

    void setPathToFile(const QString &path);

    void setPathToFile(QFile *);

private:
    Ui::UserInterface *ui;
    QHBoxLayout *centralHLayout;
    QVector<BoxContainer *> m_listePlayers;
    QString m_competitionName;
    QString m_OrgansationName;
    QString m_about;

    QVector<QString> listeOfQuestions;
    QTextStream *fileManip;
    QLineEdit *questionField;
    QString m_currentQuestion;
    QString m_answer;
    int currentIndex;
    QFile *questionFile;
    QString pathToFile;

    void createDefaultBottomDockWidget();

    void createMenuBar();

    void openQuestionFile();

    // void createStatusBar();
    Q_DISABLE_COPY(UserInterface);
};

#endif // USERINTERFACE_H
