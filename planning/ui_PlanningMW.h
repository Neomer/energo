/********************************************************************************
** Form generated from reading UI file 'PlanningMW.ui'
**
** Created: Tue 22. May 15:32:07 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANNINGMW_H
#define UI_PLANNINGMW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "datepicker.h"

QT_BEGIN_NAMESPACE

class Ui_PlanningMW
{
public:
    QAction *actQuit;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *twObjects;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    DatePicker *txtDate;
    QLabel *label_2;
    QComboBox *cmbMeasuringLength;
    QPushButton *cmdRefresh;
    QPushButton *cmdExcel;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *twData;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdExit;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *PlanningMW)
    {
        if (PlanningMW->objectName().isEmpty())
            PlanningMW->setObjectName(QString::fromUtf8("PlanningMW"));
        PlanningMW->resize(736, 625);
        actQuit = new QAction(PlanningMW);
        actQuit->setObjectName(QString::fromUtf8("actQuit"));
        centralWidget = new QWidget(PlanningMW);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 711, 571));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setSpacing(6);
        mainLayout->setContentsMargins(11, 11, 11, 11);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        twObjects = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        twObjects->setHeaderItem(__qtreewidgetitem);
        twObjects->setObjectName(QString::fromUtf8("twObjects"));
        twObjects->header()->setVisible(false);

        horizontalLayout->addWidget(twObjects);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        txtDate = new DatePicker(verticalLayoutWidget);
        txtDate->setObjectName(QString::fromUtf8("txtDate"));
        txtDate->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_3->addWidget(txtDate);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        cmbMeasuringLength = new QComboBox(verticalLayoutWidget);
        cmbMeasuringLength->setObjectName(QString::fromUtf8("cmbMeasuringLength"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cmbMeasuringLength->sizePolicy().hasHeightForWidth());
        cmbMeasuringLength->setSizePolicy(sizePolicy);
        cmbMeasuringLength->setMinimumSize(QSize(80, 0));
        cmbMeasuringLength->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_3->addWidget(cmbMeasuringLength);

        cmdRefresh = new QPushButton(verticalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/planning/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);
        cmdRefresh->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(cmdRefresh);

        cmdExcel = new QPushButton(verticalLayoutWidget);
        cmdExcel->setObjectName(QString::fromUtf8("cmdExcel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/planning/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdExcel->setIcon(icon1);
        cmdExcel->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(cmdExcel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        twData = new QTableWidget(verticalLayoutWidget);
        twData->setObjectName(QString::fromUtf8("twData"));
        twData->setEditTriggers(QAbstractItemView::AllEditTriggers);
        twData->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(twData);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(1, 1);

        mainLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 6, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_2->addWidget(cmdSave);

        cmdExit = new QPushButton(verticalLayoutWidget);
        cmdExit->setObjectName(QString::fromUtf8("cmdExit"));

        horizontalLayout_2->addWidget(cmdExit);


        mainLayout->addLayout(horizontalLayout_2);

        PlanningMW->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlanningMW);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 736, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        PlanningMW->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlanningMW);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PlanningMW->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actQuit);

        retranslateUi(PlanningMW);

        QMetaObject::connectSlotsByName(PlanningMW);
    } // setupUi

    void retranslateUi(QMainWindow *PlanningMW)
    {
        PlanningMW->setWindowTitle(QApplication::translate("PlanningMW", "PlanningMW", 0, QApplication::UnicodeUTF8));
        actQuit->setText(QApplication::translate("PlanningMW", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlanningMW", "\320\224\320\260\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlanningMW", "\320\225\320\264\320\270\320\275\320\270\321\206\320\260 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        cmdRefresh->setText(QString());
        cmdExcel->setText(QString());
        cmdSave->setText(QApplication::translate("PlanningMW", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdExit->setText(QApplication::translate("PlanningMW", "PushButton", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("PlanningMW", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlanningMW: public Ui_PlanningMW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANNINGMW_H
