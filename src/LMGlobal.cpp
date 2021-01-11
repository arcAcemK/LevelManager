//
// Created by faouzi on 1/11/21.
//

#include "include/LMGlobal.h"

void LMG::setIcon(QLabel* l, const QString &iconPath, QSize iconSize)
{
    QPixmap _icon = QPixmap(iconPath).scaled(iconSize, Qt::KeepAspectRatio);
    l->setPixmap(_icon);
}
