//
// Created by faouzi on 1/11/21.
//

#include "include/LMGlobal.h"

void LMG::set_QLabelIcon(QLabel* l, const QString &iconPath, QSize iconSize)
{
    QPixmap _icon = QPixmap(iconPath).scaled(iconSize, Qt::KeepAspectRatio);
    l->setPixmap(_icon);
}

void LMG::set_QActionShortcut(QAction* action, Qt::Key seq)
{
    auto sequence_shortcut = QKeySequence(seq);
    action->setShortcut(sequence_shortcut);
}
