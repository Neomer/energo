/********************************************************************************
** Form generated from reading UI file 'FactorySets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACTORYSETS_H
#define UI_FACTORYSETS_H

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

class Ui_FactorySets
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
    QPushButton *cmdAddObject;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *FactorySets)
    {
        if (FactorySets->objectName().isEmpty())
            FactorySets->setObjectName(QString::fromUtf8("FactorySets"));
        FactorySets->resize(543, 514);
        horizontalLayoutWidget = new QWidget(FactorySets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 511, 491));
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
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, 5, 5);
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
        cmdAddObject = new QPushButton(horizontalLayoutWidget);
        cmdAddObject->setObjectName(QString::fromUtf8("cmdAddObject"));

        verticalLayout->addWidget(cmdAddObject);

        cmdRemove = new QPushButton(horizontalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 1, 1, 1);


        mainLayout->addLayout(gridLayout);

        QWidget::setTabOrder(txtName, cmdRemove);
        QWidget::setTabOrder(cmdRemove, cmdSave);
        QWidget::setTabOrder(cmdSave, cmdDrop);

        retranslateUi(FactorySets);
        QObject::connect(cmdRemove, SIGNAL(clicked()), FactorySets, SLOT(removeItem()));
        QObject::connect(cmdAddObject, SIGNAL(clicked()), FactorySets, SLOT(appendChild()));
        QObject::connect(cmdSave, SIGNAL(clicked()), FactorySets, SLOT(saveChanges()));
        QObject::connect(cmdDrop, SIGNAL(clicked()), FactorySets, SLOT(dropChanges()));

        QMetaObject::connectSlotsByName(FactorySets);
    } // setupUi

    void retranslateUi(QWidget *FactorySets)
    {
        FactorySets->setWindowTitle(QApplication::translate("FactorySets", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FactorySets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("FactorySets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("FactorySets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FactorySets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        cmdAddObject->setText(QApplication::translate("FactorySets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\264\321\201\321\202\320\260\320\275\321\206\320\270\321\216", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("FactorySets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FactorySets: public Ui_FactorySets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACTORYSETS_H
