#ifndef BOXCONTAINER_H
#define BOXCONTAINER_H

#include "ui_/ui_BoxContainer.h"
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
    class BoxContainer;
}
QT_END_NAMESPACE

class BoxContainer: public QWidget {
  Q_OBJECT
  public slots:
    void setGroupName(QString name);
    void setGroupPicture(QString picture);
    void setGroupPicture(QPixmap picture);
    void setReward(int reward);
    void changeIncrement(int increment);
    void setPlayer1Name(QString name);
    void setPlayer2Name(QString name);

  public:
    explicit BoxContainer(QString groupName = "", QString picture = ""
                          , QString namePlayer1 = "", QString namePlayer2 = ""
                          , QWidget* parent = nullptr);

    explicit BoxContainer(BoxContainer const &box, QWidget* parent = nullptr);
    ~BoxContainer();
    QString reward() const;
    QString groupName() const;
    QList<QLabel*> playersAndGroupName() const;
    QPixmap userPict() const;

  private:
    const int pixWidth = 280;
    const int pixHeight = 300;
    int boxWidth;
    int boxHeigth;
    Ui::BoxContainer* ui;
    QPainter* elipse;
    QImage* image;
    QPixmap* pix;
    QString pixPath;
    QLabel* m_groupName;
};

#endif // BOXCONTAINER_H
