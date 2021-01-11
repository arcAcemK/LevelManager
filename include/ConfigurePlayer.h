#ifndef CONFIGUREPLAYER_H
#define CONFIGUREPLAYER_H

#include "BoxContainer.h"
#include "ui_/ui_ConfigurePlayer.h"

namespace Ui
{
    class ConfigurePlayer;
}

class ConfigurePlayer: public QWidget
{
  Q_OBJECT
  public slots:
    void setParentTabName(QString const &a_groupName);
    void setPicture(QString const &string);
    void resetToDefault();

  public:
    explicit ConfigurePlayer(QTabWidget* parent = nullptr, int index = -1);
    BoxContainer* boxContainer();
    ~ConfigurePlayer();

  private:
    BoxContainer* bx;
    QString pathToPic;
    Ui::ConfigurePlayer* ui;
    QTabWidget* m_tabParent;
    int m_index;
    QStringList bkpNamesForQuickEdit;

    void setupAddedButton();
    void handle_textEdited(QString const &newText, int index);
    void connect_fieldsEditing(QLineEdit* lineEdit, int index);
    void setUp_lineEdit_Added();
    void setGroupName(const QString &newText);
    void backupLabelValues();
    void clearLineEditField() const;
};

#endif // CONFIGUREPLAYER_H
