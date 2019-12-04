/********************************************************************************
** Form generated from reading UI file 'ObjectSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTSETS_H
#define UI_OBJECTSETS_H

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

class Ui_ObjectSets
{
public:
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtConnection;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *txtConnString;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *txtRecall;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAddFeeder;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ObjectSets)
    {
        if (ObjectSets->objectName().isEmpty())
            ObjectSets->setObjectName(QString::fromUtf8("ObjectSets"));
        ObjectSets->setEnabled(true);
        ObjectSets->resize(620, 571);
        horizontalLayoutWidget_6 = new QWidget(ObjectSets);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(10, 10, 591, 541));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget_6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(horizontalLayoutWidget_6);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtName = new QLineEdit(horizontalLayoutWidget_6);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(200, 0));
        txtName->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_2->addWidget(txtName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdSave = new QPushButton(horizontalLayoutWidget_6);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout->addWidget(cmdSave);

        cmdDrop = new QPushButton(horizontalLayoutWidget_6);
        cmdDrop->setObjectName(QString::fromUtf8("cmdDrop"));

        horizontalLayout->addWidget(cmdDrop);


        gridLayout->addLayout(horizontalLayout, 6, 1, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtConnection = new QLineEdit(horizontalLayoutWidget_6);
        txtConnection->setObjectName(QString::fromUtf8("txtConnection"));
        txtConnection->setEnabled(false);
        txtConnection->setMinimumSize(QSize(100, 0));
        txtConnection->setMaximumSize(QSize(180, 16777215));
        txtConnection->setReadOnly(true);

        horizontalLayout_3->addWidget(txtConnection);

        pushButton_3 = new QPushButton(horizontalLayoutWidget_6);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 1, 1, 1, 1);

        label_4 = new QLabel(horizontalLayoutWidget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        txtConnString = new QLineEdit(horizontalLayoutWidget_6);
        txtConnString->setObjectName(QString::fromUtf8("txtConnString"));
        txtConnString->setMinimumSize(QSize(200, 0));
        txtConnString->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(txtConnString, 2, 1, 1, 1);

        label_5 = new QLabel(horizontalLayoutWidget_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        txtRecall = new QLineEdit(horizontalLayoutWidget_6);
        txtRecall->setObjectName(QString::fromUtf8("txtRecall"));
        txtRecall->setMinimumSize(QSize(50, 0));
        txtRecall->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(txtRecall);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_4, 3, 1, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 5, -1);
        cmdAddFeeder = new QPushButton(horizontalLayoutWidget_6);
        cmdAddFeeder->setObjectName(QString::fromUtf8("cmdAddFeeder"));

        verticalLayout->addWidget(cmdAddFeeder);

        cmdRemove = new QPushButton(horizontalLayoutWidget_6);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_5, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 1, 1, 1);


        mainLayout->addLayout(gridLayout);

        QWidget::setTabOrder(txtName, txtConnection);
        QWidget::setTabOrder(txtConnection, pushButton_3);
        QWidget::setTabOrder(pushButton_3, txtConnString);
        QWidget::setTabOrder(txtConnString, txtRecall);
        QWidget::setTabOrder(txtRecall, cmdRemove);
        QWidget::setTabOrder(cmdRemove, cmdDrop);

        retranslateUi(ObjectSets);
        QObject::connect(cmdSave, SIGNAL(clicked()), ObjectSets, SLOT(saveChanges()));
        QObject::connect(cmdDrop, SIGNAL(clicked()), ObjectSets, SLOT(dropChanges()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), ObjectSets, SLOT(removeItem()));
        QObject::connect(cmdAddFeeder, SIGNAL(clicked()), ObjectSets, SLOT(appendChild()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), ObjectSets, SLOT(connectionChangeRequest()));

        QMetaObject::connectSlotsByName(ObjectSets);
    } // setupUi

    void retranslateUi(QWidget *ObjectSets)
    {
        ObjectSets->setWindowTitle(QApplication::translate("ObjectSets", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ObjectSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("ObjectSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("ObjectSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ObjectSets", "\320\241\320\276\320\265\320\264\320\270\320\275\320\265\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("ObjectSets", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214...", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ObjectSets", "\320\241\321\202\321\200\320\276\320\272\320\260 \321\201\320\262\321\217\320\267\320\270:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ObjectSets", "\320\237\320\276\320\277\321\213\321\202\320\276\320\272 \321\201\320\262\321\217\320\267\320\270:", 0, QApplication::UnicodeUTF8));
        txtRecall->setText(QApplication::translate("ObjectSets", "3", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ObjectSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        cmdAddFeeder->setText(QApplication::translate("ObjectSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\204\320\270\320\264\320\265\321\200", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("ObjectSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ObjectSets: public Ui_ObjectSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTSETS_H
