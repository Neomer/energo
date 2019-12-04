/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *mnuExit;
    QAction *mnuExport;
    QAction *mnuFind;
    QAction *mnuDebugHide;
    QAction *mnuChannelSets;
    QAction *mnuPoints;
    QAction *mnuShedule;
    QAction *mnuChannels;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabTU;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *tuLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *treeWidget;
    QGroupBox *groupBox;
    QWidget *tabDPG;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *dpgLayout;
    QHBoxLayout *horizontalLayout_4;
    QTreeWidget *twDPG;
    QGroupBox *gbDPG;
    QWidget *tabSchedule;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *scheduleLayout;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *twSchedule;
    QGroupBox *gbSchedule;
    QWidget *tabChannels;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *channelsLayout;
    QHBoxLayout *horizontalLayout_6;
    QTreeWidget *twChannels;
    QGroupBox *gbChannels;
    QWidget *tabBalans;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *balansLayout;
    QHBoxLayout *horizontalLayout_3;
    QTreeWidget *twBalans;
    QGroupBox *gbBalans;
    QWidget *tabHolydays;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *holyLayout;
    QHBoxLayout *horizontalLayout_7;
    QTreeWidget *twHoly;
    QGroupBox *gbHolydays;
    QWidget *tabUsers;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *usersLayout;
    QHBoxLayout *horizontalLayout_5;
    QTreeWidget *twUsers;
    QGroupBox *gbUsers;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(779, 769);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        mnuExit = new QAction(MainWindow);
        mnuExit->setObjectName(QString::fromUtf8("mnuExit"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuExit->setIcon(icon);
        mnuExport = new QAction(MainWindow);
        mnuExport->setObjectName(QString::fromUtf8("mnuExport"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuExport->setIcon(icon1);
        mnuFind = new QAction(MainWindow);
        mnuFind->setObjectName(QString::fromUtf8("mnuFind"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuFind->setIcon(icon2);
        mnuDebugHide = new QAction(MainWindow);
        mnuDebugHide->setObjectName(QString::fromUtf8("mnuDebugHide"));
        mnuChannelSets = new QAction(MainWindow);
        mnuChannelSets->setObjectName(QString::fromUtf8("mnuChannelSets"));
        mnuPoints = new QAction(MainWindow);
        mnuPoints->setObjectName(QString::fromUtf8("mnuPoints"));
        mnuPoints->setCheckable(true);
        mnuPoints->setChecked(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/images/tu.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuPoints->setIcon(icon3);
        mnuShedule = new QAction(MainWindow);
        mnuShedule->setObjectName(QString::fromUtf8("mnuShedule"));
        mnuShedule->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/images/shedule.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuShedule->setIcon(icon4);
        mnuChannels = new QAction(MainWindow);
        mnuChannels->setObjectName(QString::fromUtf8("mnuChannels"));
        mnuChannels->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/images/irkick.png"), QSize(), QIcon::Normal, QIcon::Off);
        mnuChannels->setIcon(icon5);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 761, 691));
        tabTU = new QWidget();
        tabTU->setObjectName(QString::fromUtf8("tabTU"));
        horizontalLayoutWidget = new QWidget(tabTU);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 12, 630, 491));
        tuLayout = new QHBoxLayout(horizontalLayoutWidget);
        tuLayout->setSpacing(6);
        tuLayout->setContentsMargins(11, 11, 11, 11);
        tuLayout->setObjectName(QString::fromUtf8("tuLayout"));
        tuLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        treeWidget = new QTreeWidget(horizontalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMinimumSize(QSize(300, 411));
        treeWidget->setMaximumSize(QSize(350, 11111111));
        treeWidget->header()->setVisible(false);
        treeWidget->header()->setCascadingSectionResizes(false);
        treeWidget->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(treeWidget);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(300, 0));

        horizontalLayout->addWidget(groupBox);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        tuLayout->addLayout(horizontalLayout);

        tabWidget->addTab(tabTU, QString());
        tabDPG = new QWidget();
        tabDPG->setObjectName(QString::fromUtf8("tabDPG"));
        horizontalLayoutWidget_4 = new QWidget(tabDPG);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 0, 741, 661));
        dpgLayout = new QHBoxLayout(horizontalLayoutWidget_4);
        dpgLayout->setSpacing(6);
        dpgLayout->setContentsMargins(11, 11, 11, 11);
        dpgLayout->setObjectName(QString::fromUtf8("dpgLayout"));
        dpgLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        twDPG = new QTreeWidget(horizontalLayoutWidget_4);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        twDPG->setHeaderItem(__qtreewidgetitem1);
        twDPG->setObjectName(QString::fromUtf8("twDPG"));
        sizePolicy1.setHeightForWidth(twDPG->sizePolicy().hasHeightForWidth());
        twDPG->setSizePolicy(sizePolicy1);
        twDPG->setMinimumSize(QSize(300, 411));
        twDPG->setMaximumSize(QSize(350, 11111111));
        twDPG->header()->setVisible(false);
        twDPG->header()->setCascadingSectionResizes(false);

        horizontalLayout_4->addWidget(twDPG);

        gbDPG = new QGroupBox(horizontalLayoutWidget_4);
        gbDPG->setObjectName(QString::fromUtf8("gbDPG"));
        sizePolicy2.setHeightForWidth(gbDPG->sizePolicy().hasHeightForWidth());
        gbDPG->setSizePolicy(sizePolicy2);
        gbDPG->setMinimumSize(QSize(300, 0));

        horizontalLayout_4->addWidget(gbDPG);

        horizontalLayout_4->setStretch(1, 3);

        dpgLayout->addLayout(horizontalLayout_4);

        tabWidget->addTab(tabDPG, QString());
        tabSchedule = new QWidget();
        tabSchedule->setObjectName(QString::fromUtf8("tabSchedule"));
        horizontalLayoutWidget_3 = new QWidget(tabSchedule);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 10, 731, 641));
        scheduleLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        scheduleLayout->setSpacing(6);
        scheduleLayout->setContentsMargins(11, 11, 11, 11);
        scheduleLayout->setObjectName(QString::fromUtf8("scheduleLayout"));
        scheduleLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        twSchedule = new QTreeWidget(horizontalLayoutWidget_3);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QString::fromUtf8("1"));
        twSchedule->setHeaderItem(__qtreewidgetitem2);
        twSchedule->setObjectName(QString::fromUtf8("twSchedule"));
        twSchedule->header()->setVisible(false);

        horizontalLayout_2->addWidget(twSchedule);

        gbSchedule = new QGroupBox(horizontalLayoutWidget_3);
        gbSchedule->setObjectName(QString::fromUtf8("gbSchedule"));

        horizontalLayout_2->addWidget(gbSchedule);

        horizontalLayout_2->setStretch(1, 3);

        scheduleLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabSchedule, QString());
        tabChannels = new QWidget();
        tabChannels->setObjectName(QString::fromUtf8("tabChannels"));
        horizontalLayoutWidget_7 = new QWidget(tabChannels);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(10, 0, 741, 661));
        channelsLayout = new QHBoxLayout(horizontalLayoutWidget_7);
        channelsLayout->setSpacing(6);
        channelsLayout->setContentsMargins(11, 11, 11, 11);
        channelsLayout->setObjectName(QString::fromUtf8("channelsLayout"));
        channelsLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(6, 6, 6, 6);
        twChannels = new QTreeWidget(horizontalLayoutWidget_7);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setText(0, QString::fromUtf8("1"));
        twChannels->setHeaderItem(__qtreewidgetitem3);
        twChannels->setObjectName(QString::fromUtf8("twChannels"));
        sizePolicy1.setHeightForWidth(twChannels->sizePolicy().hasHeightForWidth());
        twChannels->setSizePolicy(sizePolicy1);
        twChannels->setMinimumSize(QSize(300, 411));
        twChannels->setMaximumSize(QSize(350, 11111111));
        twChannels->header()->setVisible(false);
        twChannels->header()->setCascadingSectionResizes(false);

        horizontalLayout_6->addWidget(twChannels);

        gbChannels = new QGroupBox(horizontalLayoutWidget_7);
        gbChannels->setObjectName(QString::fromUtf8("gbChannels"));
        sizePolicy2.setHeightForWidth(gbChannels->sizePolicy().hasHeightForWidth());
        gbChannels->setSizePolicy(sizePolicy2);
        gbChannels->setMinimumSize(QSize(300, 0));

        horizontalLayout_6->addWidget(gbChannels);

        horizontalLayout_6->setStretch(1, 3);

        channelsLayout->addLayout(horizontalLayout_6);

        tabWidget->addTab(tabChannels, QString());
        tabBalans = new QWidget();
        tabBalans->setObjectName(QString::fromUtf8("tabBalans"));
        horizontalLayoutWidget_2 = new QWidget(tabBalans);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 20, 630, 491));
        balansLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        balansLayout->setSpacing(6);
        balansLayout->setContentsMargins(11, 11, 11, 11);
        balansLayout->setObjectName(QString::fromUtf8("balansLayout"));
        balansLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        twBalans = new QTreeWidget(horizontalLayoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem();
        __qtreewidgetitem4->setText(0, QString::fromUtf8("1"));
        twBalans->setHeaderItem(__qtreewidgetitem4);
        twBalans->setObjectName(QString::fromUtf8("twBalans"));
        sizePolicy1.setHeightForWidth(twBalans->sizePolicy().hasHeightForWidth());
        twBalans->setSizePolicy(sizePolicy1);
        twBalans->setMinimumSize(QSize(300, 411));
        twBalans->setMaximumSize(QSize(350, 11111111));
        twBalans->header()->setVisible(false);
        twBalans->header()->setCascadingSectionResizes(false);
        twBalans->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_3->addWidget(twBalans);

        gbBalans = new QGroupBox(horizontalLayoutWidget_2);
        gbBalans->setObjectName(QString::fromUtf8("gbBalans"));
        sizePolicy2.setHeightForWidth(gbBalans->sizePolicy().hasHeightForWidth());
        gbBalans->setSizePolicy(sizePolicy2);
        gbBalans->setMinimumSize(QSize(300, 0));

        horizontalLayout_3->addWidget(gbBalans);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);

        balansLayout->addLayout(horizontalLayout_3);

        tabWidget->addTab(tabBalans, QString());
        tabHolydays = new QWidget();
        tabHolydays->setObjectName(QString::fromUtf8("tabHolydays"));
        horizontalLayoutWidget_6 = new QWidget(tabHolydays);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(10, 0, 741, 661));
        holyLayout = new QHBoxLayout(horizontalLayoutWidget_6);
        holyLayout->setSpacing(6);
        holyLayout->setContentsMargins(11, 11, 11, 11);
        holyLayout->setObjectName(QString::fromUtf8("holyLayout"));
        holyLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(6, 6, 6, 6);
        twHoly = new QTreeWidget(horizontalLayoutWidget_6);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem();
        __qtreewidgetitem5->setText(0, QString::fromUtf8("1"));
        twHoly->setHeaderItem(__qtreewidgetitem5);
        twHoly->setObjectName(QString::fromUtf8("twHoly"));
        sizePolicy1.setHeightForWidth(twHoly->sizePolicy().hasHeightForWidth());
        twHoly->setSizePolicy(sizePolicy1);
        twHoly->setMinimumSize(QSize(300, 411));
        twHoly->setMaximumSize(QSize(350, 11111111));
        twHoly->header()->setVisible(false);
        twHoly->header()->setCascadingSectionResizes(false);

        horizontalLayout_7->addWidget(twHoly);

        gbHolydays = new QGroupBox(horizontalLayoutWidget_6);
        gbHolydays->setObjectName(QString::fromUtf8("gbHolydays"));
        sizePolicy2.setHeightForWidth(gbHolydays->sizePolicy().hasHeightForWidth());
        gbHolydays->setSizePolicy(sizePolicy2);
        gbHolydays->setMinimumSize(QSize(300, 0));

        horizontalLayout_7->addWidget(gbHolydays);

        horizontalLayout_7->setStretch(1, 3);

        holyLayout->addLayout(horizontalLayout_7);

        tabWidget->addTab(tabHolydays, QString());
        tabUsers = new QWidget();
        tabUsers->setObjectName(QString::fromUtf8("tabUsers"));
        horizontalLayoutWidget_5 = new QWidget(tabUsers);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(40, 10, 630, 491));
        usersLayout = new QHBoxLayout(horizontalLayoutWidget_5);
        usersLayout->setSpacing(6);
        usersLayout->setContentsMargins(11, 11, 11, 11);
        usersLayout->setObjectName(QString::fromUtf8("usersLayout"));
        usersLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        twUsers = new QTreeWidget(horizontalLayoutWidget_5);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem();
        __qtreewidgetitem6->setText(0, QString::fromUtf8("1"));
        twUsers->setHeaderItem(__qtreewidgetitem6);
        twUsers->setObjectName(QString::fromUtf8("twUsers"));
        sizePolicy1.setHeightForWidth(twUsers->sizePolicy().hasHeightForWidth());
        twUsers->setSizePolicy(sizePolicy1);
        twUsers->setMinimumSize(QSize(300, 411));
        twUsers->setMaximumSize(QSize(350, 11111111));
        twUsers->header()->setVisible(false);
        twUsers->header()->setCascadingSectionResizes(false);
        twUsers->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_5->addWidget(twUsers);

        gbUsers = new QGroupBox(horizontalLayoutWidget_5);
        gbUsers->setObjectName(QString::fromUtf8("gbUsers"));
        sizePolicy2.setHeightForWidth(gbUsers->sizePolicy().hasHeightForWidth());
        gbUsers->setSizePolicy(sizePolicy2);
        gbUsers->setMinimumSize(QSize(300, 0));

        horizontalLayout_5->addWidget(gbUsers);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 3);

        usersLayout->addLayout(horizontalLayout_5);

        tabWidget->addTab(tabUsers, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 779, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::TopToolBarArea);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(mnuFind);
        menu->addAction(mnuExport);
        menu->addSeparator();
        menu->addAction(mnuExit);
        menu_2->addAction(mnuChannelSets);
        menu_2->addSeparator();
        menu_2->addAction(mnuDebugHide);
        mainToolBar->addAction(mnuFind);

        retranslateUi(MainWindow);
        QObject::connect(mnuExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Energo - \320\232\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\202\320\276\321\200", 0, QApplication::UnicodeUTF8));
        mnuExit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        mnuExport->setText(QApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202...", 0, QApplication::UnicodeUTF8));
        mnuFind->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", 0, QApplication::UnicodeUTF8));
        mnuDebugHide->setText(QApplication::translate("MainWindow", "\320\241\320\272\321\200\321\213\321\202\321\214 \320\276\320\272\320\275\320\276 \320\276\321\202\320\273\320\260\320\264\320\272\320\270", 0, QApplication::UnicodeUTF8));
        mnuChannelSets->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\272\320\260\320\275\320\260\320\273\320\276\320\262 \321\201\320\262\321\217\320\267\320\270", 0, QApplication::UnicodeUTF8));
        mnuPoints->setText(QApplication::translate("MainWindow", "\320\242\320\276\321\207\320\272\320\270 \321\203\321\207\320\265\321\202\320\260", 0, QApplication::UnicodeUTF8));
        mnuShedule->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\265\321\200\320\265\320\264\321\214 \320\276\320\277\321\200\320\276\321\201\320\260", 0, QApplication::UnicodeUTF8));
        mnuChannels->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\260\320\273\321\213 \321\201\320\262\321\217\320\267\320\270", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabTU), QString());
        gbDPG->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabDPG), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
        gbSchedule->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\267\320\260\320\264\320\260\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabSchedule), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        gbChannels->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabChannels), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
        gbBalans->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabBalans), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
        gbHolydays->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabHolydays), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
        gbUsers->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tabUsers), QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
