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

class LMMainUi: public QMainWindow
{
  Q_OBJECT
  public slots:
    void openAbout();
    void openCredit();
    void prevQuestion();
    void nextQuestion();
    void toggle_menuBar_visibility();
    void toggle_fullscreen();
    void quit() { close(); }; //needed in handle_triggeredSignal()

  private:
    LMMainUi(QWidget* parent = nullptr);

  public:
    LMMainUi(const QList<LMProfile*> &profiles, QWidget* parent = nullptr);
    explicit LMMainUi(LMMainUi &main_ui, QWidget* parent = nullptr);
    ~LMMainUi();

    void addGroupProfile(LMProfile* a_profile = nullptr);
    void setProfilesList(const QList<LMProfile*> &list);
    void setAbout(const QString &);
    void setCompetitionName(const QString &);
    void setOrganisationName(const QString &);
    const QString &currentQuestion();
    const QList<LMProfile*> &profilesList();
    void setPathToFile(const QString &path);
    static QString defaultQstFile() { return ":/ecriture.txt"; }
  private:
    Ui::LMMainUi* ui;
    QList<LMProfile*> m_profilesList;
    QString m_competitionName;
    QString m_OrganisationName;
    QString m_about;

    QStringList questionList;
    QString m_currentQuestion;
    QString m_answer;
    int currentIndex;
    QString pathToFile;

    void handle_triggeredSignal(QAction* a, VoidHandler handler) const;
    void setup_questionsFields();
    void setup_menuBar_event();
    void open_questionFile();
    void handle_sequenceKey_shortcut(Qt::Key seq, VoidHandler handler);
    Q_DISABLE_COPY(LMMainUi);
};

#endif // LMMAINUI_H
