#ifndef LMMAINUI_H
#define LMMAINUI_H

#include <QMainWindow>
#include "LMProfile.h"
#include "ui_/ui_LMMainUi.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LMMainUi;
}
QT_END_NAMESPACE

class LMMainUi;

using VoidHandler = void (LMMainUi::*)();
using Interface = LMMainUi;

class LMMainUi: public QMainWindow
{
  Q_OBJECT
  public slots:
    void openAbout();
    void openCredit();
    void prevQuestion();
    void nextQuestion();
    void hideMenuBar();
    void toggleFullscreen();
    void quit() { close(); }; //needed in trap_QAction_triggeredSignal()

  public:
    explicit LMMainUi(QWidget* parent = nullptr);
    explicit LMMainUi(QList<LMProfile*> listePlayers
                      , QWidget* parent = nullptr);
    explicit LMMainUi(QVector<LMProfile*> listePlayers
                      , QWidget* parent = nullptr);
    explicit LMMainUi(LMMainUi const &interf
                      , QWidget* parent = nullptr);
    ~LMMainUi();
    void addPlayer(LMProfile* player = nullptr);
    void setListePlayers(QList<LMProfile*> liste);
    void setListePlayers(QVector<LMProfile*> liste);
    void setAbout(QString);
    void setCompetitionName(QString);
    void setOrganisationName(QString);
    QString currentQuestion();
    QVector<LMProfile*> listePlayers();
    void setPathToFile(const QString &path);
    void setPathToFile(QFile*);

  private:
    Ui::LMMainUi* ui;
    QHBoxLayout* centralHLayout;
    QVector<LMProfile*> m_listePlayers;
    QString m_competitionName;
    QString m_OrgansationName;
    QString m_about;

    QVector<QString> listeOfQuestions;
    QTextStream* fileManip;
    QLineEdit* questionField;
    QString m_currentQuestion;
    QString m_answer;
    int currentIndex;
    QFile* questionFile;
    QString pathToFile;

    void handle_triggeredSignal(QAction* a, VoidHandler handler) const;
    void createDefaultBottomDockWidget();
    void createMenuBar();
    void openQuestionFile();
    // void createStatusBar();
    Q_DISABLE_COPY(LMMainUi);
};

#endif // LMMAINUI_H
