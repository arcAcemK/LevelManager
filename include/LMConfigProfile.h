#ifndef LMCONFIGPROFILE_H
#define LMCONFIGPROFILE_H

#include "LMProfile.h"
#include "ui_/ui_LMConfigProfile.h"

namespace Ui
{
    class LMConfigProfile;
}
class LMConfigProfile;

using LMCP = LMConfigProfile;

class LMConfigProfile: public QWidget
{
  Q_OBJECT
  public slots:
    void setParentTabName(QString const &a_groupName);
    void setPicture(QString const &string);
    void resetToDefault();

  public:
    explicit LMConfigProfile(QTabWidget* parent = nullptr, int index = -1);
    LMProfile* boxContainer();
    ~LMConfigProfile();

  private:
    LMProfile* bx;
    QString pathToPic;
    Ui::LMConfigProfile* ui;
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

#endif // LMCONFIGPROFILE_H
