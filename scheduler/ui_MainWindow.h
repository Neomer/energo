/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Tue 22. Jan 11:03:43 2013
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actStart;
    QAction *actStop;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QTreeWidget *twSchedule;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTableWidget *twStatus;
    QLabel *label;
    QPlainTextEdit *txtConsole;
    QMenuBar *menubar;
    QMenu *menu;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 640);
        actStart = new QAction(MainWindow);
        actStart->setObjectName(QString::fromUtf8("actStart"));
        actStart->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/scheduler/images/go-next-view.png"), QSize(), QIcon::Normal, QIcon::Off);
        actStart->setIcon(icon);
        actStart->setMenuRole(QAction::ApplicationSpecificRole);
        actStop = new QAction(MainWindow);
        actStop->setObjectName(QString::fromUtf8("actStop"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/scheduler/images/media-playback-stop-7.png"), QSize(), QIcon::Normal, QIcon::Off);
        actStop->setIcon(icon1);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 781, 551));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setContentsMargins(6, 6, 6, 6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        twSchedule = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        twSchedule->setHeaderItem(__qtreewidgetitem);
        twSchedule->setObjectName(QString::fromUtf8("twSchedule"));
        twSchedule->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twSchedule->setProperty("showDropIndicator", QVariant(false));
        twSchedule->setExpandsOnDoubleClick(false);
        twSchedule->header()->setVisible(false);

        gridLayout->addWidget(twSchedule, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, -1, -1, -1);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        twStatus = new QTableWidget(verticalLayoutWidget);
        twStatus->setObjectName(QString::fromUtf8("twStatus"));
        twStatus->horizontalHeader()->setVisible(false);
        twStatus->verticalHeader()->setVisible(false);
        twStatus->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(twStatus);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        txtConsole = new QPlainTextEdit(verticalLayoutWidget);
        txtConsole->setObjectName(QString::fromUtf8("txtConsole"));
        txtConsole->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtConsole->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(txtConsole);

        verticalLayout->setStretch(3, 1);

        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 2);

        mainLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        toolBar->addAction(actStart);
        toolBar->addAction(actStop);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Energo - \320\224\320\270\321\201\320\277\320\265\321\202\321\207\320\265\321\200 \320\260\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\263\320\276 \320\276\320\277\321\200\320\276\321\201\320\260", 0, QApplication::UnicodeUTF8));
        actStart->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        actStop->setText(QApplication::translate("MainWindow", "\320\236\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \320\267\320\260\320\264\320\260\321\207\320\270:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\275\321\201\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
