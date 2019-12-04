/********************************************************************************
** Form generated from reading UI file 'CHGSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHGSETS_H
#define UI_CHGSETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CHGSets
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendarWidget;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *cmdCreateDay;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *cmdCreateMonth;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdRemoveGroup;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *CHGSets)
    {
        if (CHGSets->objectName().isEmpty())
            CHGSets->setObjectName(QString::fromUtf8("CHGSets"));
        CHGSets->resize(603, 525);
        horizontalLayoutWidget = new QWidget(CHGSets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 571, 511));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, -1);
        calendarWidget = new QCalendarWidget(horizontalLayoutWidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        horizontalLayout->addWidget(calendarWidget);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 0, -1, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        cmdCreateDay = new QPushButton(horizontalLayoutWidget);
        cmdCreateDay->setObjectName(QString::fromUtf8("cmdCreateDay"));

        horizontalLayout_5->addWidget(cmdCreateDay);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 0, -1, -1);
        cmdCreateMonth = new QPushButton(horizontalLayoutWidget);
        cmdCreateMonth->setObjectName(QString::fromUtf8("cmdCreateMonth"));

        horizontalLayout_7->addWidget(cmdCreateMonth);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_2->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtName = new QLineEdit(horizontalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));

        horizontalLayout_3->addWidget(txtName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 6, -1);
        cmdRemoveGroup = new QPushButton(horizontalLayoutWidget);
        cmdRemoveGroup->setObjectName(QString::fromUtf8("cmdRemoveGroup"));

        verticalLayout->addWidget(cmdRemoveGroup);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 3, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cmdSave = new QPushButton(horizontalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_2->addWidget(cmdSave);

        cmdDrop = new QPushButton(horizontalLayoutWidget);
        cmdDrop->setObjectName(QString::fromUtf8("cmdDrop"));

        horizontalLayout_2->addWidget(cmdDrop);


        gridLayout->addLayout(horizontalLayout_2, 6, 1, 1, 1);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(CHGSets);

        QMetaObject::connectSlotsByName(CHGSets);
    } // setupUi

    void retranslateUi(QWidget *CHGSets)
    {
        CHGSets->setWindowTitle(QApplication::translate("CHGSets", "Form", 0, QApplication::UnicodeUTF8));
        cmdCreateDay->setText(QApplication::translate("CHGSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\264\320\265\320\275\321\214", 0, QApplication::UnicodeUTF8));
        cmdCreateMonth->setText(QApplication::translate("CHGSets", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\267\320\260 \320\274\320\265\321\201\321\217\321\206", 0, QApplication::UnicodeUTF8));
        cmdRemoveGroup->setText(QApplication::translate("CHGSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\263\321\200\321\203\320\277\320\277\321\203", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("CHGSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("CHGSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CHGSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CHGSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CHGSets", "\320\232\320\260\320\273\320\265\320\275\320\264\320\260\321\200\321\214:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CHGSets: public Ui_CHGSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHGSETS_H
