/********************************************************************************
** Form generated from reading UI file 'ChannelSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNELSETS_H
#define UI_CHANNELSETS_H

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

class Ui_ChannelSets
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *txtName;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *txtNumber;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *txtType;
    QPushButton *cmdSelectType;
    QSpacerItem *horizontalSpacer_10;

    void setupUi(QWidget *ChannelSets)
    {
        if (ChannelSets->objectName().isEmpty())
            ChannelSets->setObjectName(QString::fromUtf8("ChannelSets"));
        ChannelSets->resize(547, 501);
        horizontalLayoutWidget_2 = new QWidget(ChannelSets);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 0, 511, 491));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 5, 5, 5);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        cmdSave = new QPushButton(horizontalLayoutWidget_2);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_7->addWidget(cmdSave);

        cmdDrop = new QPushButton(horizontalLayoutWidget_2);
        cmdDrop->setObjectName(QString::fromUtf8("cmdDrop"));

        horizontalLayout_7->addWidget(cmdDrop);


        gridLayout_2->addLayout(horizontalLayout_7, 7, 1, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        txtName = new QLineEdit(horizontalLayoutWidget_2);
        txtName->setObjectName(QString::fromUtf8("txtName"));

        horizontalLayout_8->addWidget(txtName);

        pushButton = new QPushButton(horizontalLayoutWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_8->addWidget(pushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        gridLayout_2->addLayout(horizontalLayout_8, 0, 1, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, 6, -1);
        cmdRemove = new QPushButton(horizontalLayoutWidget_2);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout_2->addWidget(cmdRemove);


        horizontalLayout_9->addLayout(verticalLayout_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        gridLayout_2->addLayout(horizontalLayout_9, 3, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 5, 1, 1, 1);

        label_7 = new QLabel(horizontalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        txtNumber = new QLineEdit(horizontalLayoutWidget_2);
        txtNumber->setObjectName(QString::fromUtf8("txtNumber"));
        txtNumber->setMaximumSize(QSize(75, 16777215));
        txtNumber->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(txtNumber);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_9);


        gridLayout_2->addLayout(horizontalLayout_10, 1, 1, 1, 1);

        label_8 = new QLabel(horizontalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        txtType = new QLineEdit(horizontalLayoutWidget_2);
        txtType->setObjectName(QString::fromUtf8("txtType"));
        txtType->setEnabled(false);
        txtType->setReadOnly(false);

        horizontalLayout_11->addWidget(txtType);

        cmdSelectType = new QPushButton(horizontalLayoutWidget_2);
        cmdSelectType->setObjectName(QString::fromUtf8("cmdSelectType"));
        sizePolicy.setHeightForWidth(cmdSelectType->sizePolicy().hasHeightForWidth());
        cmdSelectType->setSizePolicy(sizePolicy);
        cmdSelectType->setMaximumSize(QSize(45, 16777215));

        horizontalLayout_11->addWidget(cmdSelectType);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_10);


        gridLayout_2->addLayout(horizontalLayout_11, 2, 1, 1, 1);


        mainLayout->addLayout(gridLayout_2);


        retranslateUi(ChannelSets);

        QMetaObject::connectSlotsByName(ChannelSets);
    } // setupUi

    void retranslateUi(QWidget *ChannelSets)
    {
        ChannelSets->setWindowTitle(QApplication::translate("ChannelSets", "Form", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ChannelSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("ChannelSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("ChannelSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ChannelSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ChannelSets", "...", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("ChannelSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ChannelSets", "\320\235\320\276\320\274\320\265\321\200:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("ChannelSets", "\320\242\320\270\320\277 \320\264\320\260\320\275\320\275\321\213\321\205:", 0, QApplication::UnicodeUTF8));
        cmdSelectType->setText(QApplication::translate("ChannelSets", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChannelSets: public Ui_ChannelSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNELSETS_H
