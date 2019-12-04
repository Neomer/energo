/********************************************************************************
** Form generated from reading UI file 'balanscreate.ui'
**
** Created: Wed 1. Feb 13:27:43 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANSCREATE_H
#define UI_BALANSCREATE_H

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
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalansCreate
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *twSelected;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *cmdAdd;
    QPushButton *cmdRemove;
    QSpacerItem *verticalSpacer_3;
    QTableWidget *twTotal;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdCancel;

    void setupUi(QDialog *BalansCreate)
    {
        if (BalansCreate->objectName().isEmpty())
            BalansCreate->setObjectName(QString::fromUtf8("BalansCreate"));
        BalansCreate->resize(852, 521);
        verticalLayoutWidget = new QWidget(BalansCreate);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 831, 501));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(6, 6, 6, 6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        twSelected = new QTableWidget(verticalLayoutWidget);
        twSelected->setObjectName(QString::fromUtf8("twSelected"));

        horizontalLayout_2->addWidget(twSelected);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 5, 5, 3);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        cmdAdd = new QPushButton(verticalLayoutWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));
        cmdAdd->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(cmdAdd);

        cmdRemove = new QPushButton(verticalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));
        cmdRemove->setMaximumSize(QSize(30, 16777215));

        verticalLayout->addWidget(cmdRemove);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout);

        twTotal = new QTableWidget(verticalLayoutWidget);
        twTotal->setObjectName(QString::fromUtf8("twTotal"));

        horizontalLayout_2->addWidget(twTotal);


        mainLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(6, 5, 6, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout->addWidget(cmdSave);

        cmdCancel = new QPushButton(verticalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);


        mainLayout->addLayout(horizontalLayout);


        retranslateUi(BalansCreate);
        QObject::connect(cmdCancel, SIGNAL(clicked()), BalansCreate, SLOT(close()));
        QObject::connect(twTotal, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), BalansCreate, SLOT(appendItem(QTableWidgetItem*)));
        QObject::connect(twSelected, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), BalansCreate, SLOT(removeItem(QTableWidgetItem*)));
        QObject::connect(cmdRemove, SIGNAL(clicked()), BalansCreate, SLOT(removeItemBtnClicked()));
        QObject::connect(cmdAdd, SIGNAL(clicked()), BalansCreate, SLOT(addItemBtnClicked()));

        QMetaObject::connectSlotsByName(BalansCreate);
    } // setupUi

    void retranslateUi(QDialog *BalansCreate)
    {
        BalansCreate->setWindowTitle(QApplication::translate("BalansCreate", "Dialog", 0, QApplication::UnicodeUTF8));
        cmdAdd->setText(QApplication::translate("BalansCreate", "<<", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("BalansCreate", ">>", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("BalansCreate", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("BalansCreate", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BalansCreate: public Ui_BalansCreate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANSCREATE_H
