/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 22. Jun 13:05:24 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *mnuExit;
    QAction *action_3;
    QAction *mnuSaveAs;
    QAction *mnuCheckData;
    QAction *actPrint;
    QAction *actPrintPreview;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *mnuReports;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(896, 680);
        mnuExit = new QAction(MainWindow);
        mnuExit->setObjectName(QString::fromUtf8("mnuExit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuExit->setIcon(icon);
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_3->setIcon(icon1);
        mnuSaveAs = new QAction(MainWindow);
        mnuSaveAs->setObjectName(QString::fromUtf8("mnuSaveAs"));
        mnuSaveAs->setIcon(icon1);
        mnuCheckData = new QAction(MainWindow);
        mnuCheckData->setObjectName(QString::fromUtf8("mnuCheckData"));
        actPrint = new QAction(MainWindow);
        actPrint->setObjectName(QString::fromUtf8("actPrint"));
        actPrintPreview = new QAction(MainWindow);
        actPrintPreview->setObjectName(QString::fromUtf8("actPrintPreview"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 896, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        mnuReports = new QMenu(menuBar);
        mnuReports->setObjectName(QString::fromUtf8("mnuReports"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::TopToolBarArea);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(mnuReports->menuAction());
        menu->addAction(mnuSaveAs);
        menu->addSeparator();
        menu->addAction(actPrint);
        menu->addAction(actPrintPreview);
        menu->addSeparator();
        menu->addAction(mnuExit);

        retranslateUi(MainWindow);
        QObject::connect(mnuExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Energo - \320\236\321\202\321\207\320\265\321\202\321\213", 0, QApplication::UnicodeUTF8));
        mnuExit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202...", 0, QApplication::UnicodeUTF8));
        mnuSaveAs->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272...", 0, QApplication::UnicodeUTF8));
        mnuCheckData->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273\320\275\320\276\321\202\320\260 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        actPrint->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214...", 0, QApplication::UnicodeUTF8));
        actPrintPreview->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\262\320\260\321\200\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \320\277\321\200\320\276\321\201\320\274\320\276\321\202\321\200...", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        mnuReports->setTitle(QApplication::translate("MainWindow", "\320\236\321\202\321\207\320\265\321\202\321\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
