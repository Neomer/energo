/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created: Wed 1. Feb 13:27:43 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *verticalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cmdProperty;
    QPushButton *cmdCreate;
    QPushButton *cmdRemove;
    QSpacerItem *verticalSpacer;
    QListWidget *tvList;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(659, 378);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainForm->sizePolicy().hasHeightForWidth());
        MainForm->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(MainForm);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 631, 331));
        mainLayout = new QHBoxLayout(verticalLayoutWidget);
        mainLayout->setContentsMargins(6, 6, 6, 6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, 5, -1);
        cmdProperty = new QPushButton(verticalLayoutWidget);
        cmdProperty->setObjectName(QString::fromUtf8("cmdProperty"));

        verticalLayout_2->addWidget(cmdProperty);

        cmdCreate = new QPushButton(verticalLayoutWidget);
        cmdCreate->setObjectName(QString::fromUtf8("cmdCreate"));

        verticalLayout_2->addWidget(cmdCreate);

        cmdRemove = new QPushButton(verticalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout_2->addWidget(cmdRemove);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        tvList = new QListWidget(verticalLayoutWidget);
        tvList->setObjectName(QString::fromUtf8("tvList"));
        tvList->setMinimumSize(QSize(450, 0));

        gridLayout->addWidget(tvList, 0, 0, 1, 1);


        mainLayout->addLayout(gridLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mainLayout->addItem(horizontalSpacer);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Form", 0, QApplication::UnicodeUTF8));
        cmdProperty->setText(QApplication::translate("MainForm", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\260", 0, QApplication::UnicodeUTF8));
        cmdCreate->setText(QApplication::translate("MainForm", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("MainForm", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
