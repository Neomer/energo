/********************************************************************************
** Form generated from reading UI file 'BalansSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANSSETS_H
#define UI_BALANSSETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalansSets
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cmdSave;
    QPushButton *cmdCancel;
    QLabel *label_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *twElements;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cmdAdd;
    QPushButton *cmdRemove;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QPushButton *cmdRemoveBalans;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;

    void setupUi(QWidget *BalansSets)
    {
        if (BalansSets->objectName().isEmpty())
            BalansSets->setObjectName(QString::fromUtf8("BalansSets"));
        BalansSets->resize(653, 616);
        verticalLayoutWidget = new QWidget(BalansSets);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 631, 591));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(5, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtName = new QLineEdit(verticalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(268, 0));

        horizontalLayout->addWidget(txtName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 5, -1, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_4->addWidget(cmdSave);

        cmdCancel = new QPushButton(verticalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout_4->addWidget(cmdCancel);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        twElements = new QTableWidget(verticalLayoutWidget);
        twElements->setObjectName(QString::fromUtf8("twElements"));
        twElements->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twElements->setSelectionMode(QAbstractItemView::SingleSelection);
        twElements->setSelectionBehavior(QAbstractItemView::SelectRows);
        twElements->setWordWrap(false);
        twElements->verticalHeader()->setCascadingSectionResizes(true);
        twElements->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_5->addWidget(twElements);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, -1, -1, -1);
        cmdAdd = new QPushButton(verticalLayoutWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));

        verticalLayout_2->addWidget(cmdAdd);

        cmdRemove = new QPushButton(verticalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout_2->addWidget(cmdRemove);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        cmdRemoveBalans = new QPushButton(verticalLayoutWidget);
        cmdRemoveBalans->setObjectName(QString::fromUtf8("cmdRemoveBalans"));

        verticalLayout_3->addWidget(cmdRemoveBalans);


        horizontalLayout_6->addLayout(verticalLayout_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_6, 3, 1, 1, 1);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(BalansSets);
        QObject::connect(cmdAdd, SIGNAL(clicked()), BalansSets, SLOT(addChannels()));
        QObject::connect(cmdSave, SIGNAL(clicked()), BalansSets, SLOT(saveChanges()));
        QObject::connect(cmdCancel, SIGNAL(clicked()), BalansSets, SLOT(dropChanges()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), BalansSets, SLOT(removeChannels()));

        QMetaObject::connectSlotsByName(BalansSets);
    } // setupUi

    void retranslateUi(QWidget *BalansSets)
    {
        BalansSets->setWindowTitle(QApplication::translate("BalansSets", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BalansSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("BalansSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("BalansSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("BalansSets", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213:", 0, QApplication::UnicodeUTF8));
        cmdAdd->setText(QApplication::translate("BalansSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("BalansSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdRemoveBalans->setText(QApplication::translate("BalansSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\261\320\260\320\273\320\260\320\275\321\201\320\276\320\262\321\203\321\216 \320\263\321\200\321\203\320\277\320\277\321\203", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("BalansSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BalansSets: public Ui_BalansSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANSSETS_H
