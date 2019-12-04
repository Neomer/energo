/********************************************************************************
** Form generated from reading UI file 'ScheduleSelectElements.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULESELECTELEMENTS_H
#define UI_SCHEDULESELECTELEMENTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleSelectElements
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *twObjects;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *cmdSelect;
    QPushButton *cmdDeselect;
    QSpacerItem *verticalSpacer_2;
    QTableWidget *twSelected;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *pushButton;

    void setupUi(QDialog *ScheduleSelectElements)
    {
        if (ScheduleSelectElements->objectName().isEmpty())
            ScheduleSelectElements->setObjectName(QString::fromUtf8("ScheduleSelectElements"));
        ScheduleSelectElements->resize(942, 582);
        verticalLayoutWidget = new QWidget(ScheduleSelectElements);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 911, 561));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, -1, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        twObjects = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        twObjects->setHeaderItem(__qtreewidgetitem);
        twObjects->setObjectName(QString::fromUtf8("twObjects"));
        twObjects->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twObjects->setExpandsOnDoubleClick(false);

        horizontalLayout->addWidget(twObjects);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, -1, 6, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        cmdSelect = new QPushButton(verticalLayoutWidget);
        cmdSelect->setObjectName(QString::fromUtf8("cmdSelect"));
        cmdSelect->setMinimumSize(QSize(0, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSelect->setIcon(icon);

        verticalLayout->addWidget(cmdSelect);

        cmdDeselect = new QPushButton(verticalLayoutWidget);
        cmdDeselect->setObjectName(QString::fromUtf8("cmdDeselect"));
        cmdDeselect->setMinimumSize(QSize(0, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/deselect.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdDeselect->setIcon(icon1);

        verticalLayout->addWidget(cmdDeselect);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        twSelected = new QTableWidget(verticalLayoutWidget);
        twSelected->setObjectName(QString::fromUtf8("twSelected"));
        twSelected->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twSelected->setSelectionMode(QAbstractItemView::MultiSelection);
        twSelected->setSelectionBehavior(QAbstractItemView::SelectRows);
        twSelected->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        twSelected->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout->addWidget(twSelected);

        horizontalLayout->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, 6, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_2->addWidget(cmdSave);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);


        mainLayout->addLayout(verticalLayout_2);


        retranslateUi(ScheduleSelectElements);
        QObject::connect(pushButton, SIGNAL(clicked()), ScheduleSelectElements, SLOT(reject()));
        QObject::connect(cmdSelect, SIGNAL(clicked()), ScheduleSelectElements, SLOT(itemSelect()));
        QObject::connect(cmdDeselect, SIGNAL(clicked()), ScheduleSelectElements, SLOT(itemRemove()));
        QObject::connect(cmdSave, SIGNAL(clicked()), ScheduleSelectElements, SLOT(saveChanges()));

        QMetaObject::connectSlotsByName(ScheduleSelectElements);
    } // setupUi

    void retranslateUi(QDialog *ScheduleSelectElements)
    {
        ScheduleSelectElements->setWindowTitle(QApplication::translate("ScheduleSelectElements", "Dialog", 0, QApplication::UnicodeUTF8));
        cmdSelect->setText(QString());
        cmdDeselect->setText(QString());
        cmdSave->setText(QApplication::translate("ScheduleSelectElements", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ScheduleSelectElements", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScheduleSelectElements: public Ui_ScheduleSelectElements {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULESELECTELEMENTS_H
