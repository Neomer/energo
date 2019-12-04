/********************************************************************************
** Form generated from reading UI file 'DPGSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DPGSETS_H
#define UI_DPGSETS_H

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

class Ui_DPGSets
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdCodes;
    QPushButton *cmdAddMeasuringPoint;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtNDog;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *DPGSets)
    {
        if (DPGSets->objectName().isEmpty())
            DPGSets->setObjectName(QString::fromUtf8("DPGSets"));
        DPGSets->resize(647, 586);
        horizontalLayoutWidget = new QWidget(DPGSets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 20, 591, 541));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cmdSave = new QPushButton(horizontalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_2->addWidget(cmdSave);

        cmdDrop = new QPushButton(horizontalLayoutWidget);
        cmdDrop->setObjectName(QString::fromUtf8("cmdDrop"));

        horizontalLayout_2->addWidget(cmdDrop);


        gridLayout->addLayout(horizontalLayout_2, 7, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 6, -1);
        cmdCodes = new QPushButton(horizontalLayoutWidget);
        cmdCodes->setObjectName(QString::fromUtf8("cmdCodes"));

        verticalLayout->addWidget(cmdCodes);

        cmdAddMeasuringPoint = new QPushButton(horizontalLayoutWidget);
        cmdAddMeasuringPoint->setObjectName(QString::fromUtf8("cmdAddMeasuringPoint"));

        verticalLayout->addWidget(cmdAddMeasuringPoint);

        cmdRemove = new QPushButton(horizontalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtName = new QLineEdit(horizontalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));

        horizontalLayout_3->addWidget(txtName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        txtNDog = new QLineEdit(horizontalLayoutWidget);
        txtNDog->setObjectName(QString::fromUtf8("txtNDog"));

        horizontalLayout_5->addWidget(txtNDog);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(DPGSets);
        QObject::connect(cmdCodes, SIGNAL(clicked()), DPGSets, SLOT(editCodes()));
        QObject::connect(cmdSave, SIGNAL(clicked()), DPGSets, SLOT(saveChanges()));
        QObject::connect(cmdDrop, SIGNAL(clicked()), DPGSets, SLOT(dropChanges()));
        QObject::connect(cmdAddMeasuringPoint, SIGNAL(clicked()), DPGSets, SLOT(appendChild()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), DPGSets, SLOT(removeItem()));

        QMetaObject::connectSlotsByName(DPGSets);
    } // setupUi

    void retranslateUi(QWidget *DPGSets)
    {
        DPGSets->setWindowTitle(QApplication::translate("DPGSets", "Form", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("DPGSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("DPGSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCodes->setText(QApplication::translate("DPGSets", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\272\321\203...", 0, QApplication::UnicodeUTF8));
        cmdAddMeasuringPoint->setText(QApplication::translate("DPGSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\321\203 \320\277\320\276\321\201\321\202\320\260\320\262\320\272\320\270", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("DPGSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\263\321\200\321\203\320\277\320\277\321\203", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DPGSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DPGSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DPGSets", "\342\204\226 \320\264\320\276\320\263\320\276\320\262\320\276\321\200\320\260:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DPGSets: public Ui_DPGSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DPGSETS_H
