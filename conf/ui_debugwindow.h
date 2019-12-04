/********************************************************************************
** Form generated from reading UI file 'debugwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGWINDOW_H
#define UI_DEBUGWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugWindow
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *txtDebug;

    void setupUi(QDialog *DebugWindow)
    {
        if (DebugWindow->objectName().isEmpty())
            DebugWindow->setObjectName(QString::fromUtf8("DebugWindow"));
        DebugWindow->resize(542, 389);
        verticalLayoutWidget = new QWidget(DebugWindow);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(60, 90, 160, 80));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        txtDebug = new QPlainTextEdit(verticalLayoutWidget);
        txtDebug->setObjectName(QString::fromUtf8("txtDebug"));
        txtDebug->setTabChangesFocus(true);
        txtDebug->setUndoRedoEnabled(false);
        txtDebug->setReadOnly(true);

        verticalLayout_2->addWidget(txtDebug);


        mainLayout->addLayout(verticalLayout_2);


        retranslateUi(DebugWindow);

        QMetaObject::connectSlotsByName(DebugWindow);
    } // setupUi

    void retranslateUi(QDialog *DebugWindow)
    {
        DebugWindow->setWindowTitle(QApplication::translate("DebugWindow", "Debug", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebugWindow: public Ui_DebugWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGWINDOW_H
