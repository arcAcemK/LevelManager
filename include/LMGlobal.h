//
// Created by faouzi on 1/11/21.
//

#ifndef LEVELMANAGER_LMGLOBAL_H
#define LEVELMANAGER_LMGLOBAL_H

#include <QtWidgets>
#include <QtCore>

namespace LMGlobal
{
    void set_QLabelIcon(QLabel* l, const QString &iconPath, QSize iconSize);
    void set_QActionShortcut(QAction* action, Qt::Key seq);
};
namespace LMG = LMGlobal;

#endif //LEVELMANAGER_LMGLOBAL_H
