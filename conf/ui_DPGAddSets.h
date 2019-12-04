/********************************************************************************
** Form generated from reading UI file 'DPGAddSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPGADDSETS_H
#define UI_DPGADDSETS_H

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
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DPGAddSets
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAddGroup;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *DPGAddSets)
    {
        if (DPGAddSets->objectName().isEmpty())
            DPGAddSets->setObjectName(QString::fromUtf8("DPGAddSets"));
        DPGAddSets->resize(585, 525);
        horizontalLayoutWidget = new QWidget(DPGAddSets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(40, 20, 511, 491));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label, 0, 0, 1, 1);

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


        gridLayout->addLayout(horizontalLayout_2, 4, 1, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

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
        cmdAddGroup = new QPushButton(horizontalLayoutWidget);
        cmdAddGroup->setObjectName(QString::fromUtf8("cmdAddGroup"));

        verticalLayout->addWidget(cmdAddGroup);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(DPGAddSets);
        QObject::connect(cmdAddGroup, SIGNAL(clicked()), DPGAddSets, SLOT(appendChild()));
        QObject::connect(cmdSave, SIGNAL(clicked()), DPGAddSets, SLOT(saveChanges()));
        QObject::connect(cmdDrop, SIGNAL(clicked()), DPGAddSets, SLOT(dropChanges()));

        QMetaObject::connectSlotsByName(DPGAddSets);
    } // setupUi

    void retranslateUi(QWidget *DPGAddSets)
    {
        DPGAddSets->setWindowTitle(QApplication::translate("DPGAddSets", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DPGAddSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("DPGAddSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("DPGAddSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DPGAddSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        cmdAddGroup->setText(QApplication::translate("DPGAddSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\263\321\200\321\203\320\277\320\277\321\203", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DPGAddSets: public Ui_DPGAddSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPGADDSETS_H
