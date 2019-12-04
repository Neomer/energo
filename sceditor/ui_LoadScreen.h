/********************************************************************************
** Form generated from reading UI file 'LoadScreen.ui'
**
** Created: Wed 22. Aug 17:54:50 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADSCREEN_H
#define UI_LOADSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadScreen
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGraphicsView *gv;

    void setupUi(QWidget *LoadScreen)
    {
        if (LoadScreen->objectName().isEmpty())
            LoadScreen->setObjectName(QString::fromUtf8("LoadScreen"));
        LoadScreen->setWindowModality(Qt::NonModal);
        LoadScreen->resize(400, 300);
        verticalLayoutWidget = new QWidget(LoadScreen);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 160, 80));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gv = new QGraphicsView(verticalLayoutWidget);
        gv->setObjectName(QString::fromUtf8("gv"));
        QBrush brush(QColor(0, 0, 0, 0));
        brush.setStyle(Qt::SolidPattern);
        gv->setBackgroundBrush(brush);
        gv->setResizeAnchor(QGraphicsView::AnchorViewCenter);

        mainLayout->addWidget(gv);


        retranslateUi(LoadScreen);

        QMetaObject::connectSlotsByName(LoadScreen);
    } // setupUi

    void retranslateUi(QWidget *LoadScreen)
    {
        LoadScreen->setWindowTitle(QApplication::translate("LoadScreen", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoadScreen: public Ui_LoadScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADSCREEN_H
