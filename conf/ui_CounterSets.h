/********************************************************************************
** Form generated from reading UI file 'CounterSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTERSETS_H
#define UI_COUNTERSETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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

class Ui_CounterSets
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOk;
    QPushButton *cmdCancel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtType;
    QPushButton *cmdTypeChange;
    QCheckBox *chkCounterTypeManual;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *txtNumber;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *txtAddress;
    QLabel *label_5;
    QLineEdit *txtDepth;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *txtPassword;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *txtTimeoutRead;
    QLabel *label_7;
    QLineEdit *txtTimeoutWrite;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAddChannel;
    QPushButton *cmdAddParam;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_9;
    QLabel *label_11;
    QCheckBox *chkAllow;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *txtLogin;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_14;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLineEdit *txtMinCorrection;
    QLabel *label_16;
    QLineEdit *txtMaxCorrection;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_15;
    QCheckBox *chkTimeCorrection;

    void setupUi(QWidget *CounterSets)
    {
        if (CounterSets->objectName().isEmpty())
            CounterSets->setObjectName(QString::fromUtf8("CounterSets"));
        CounterSets->resize(629, 538);
        horizontalLayoutWidget = new QWidget(CounterSets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 617, 511));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 5, 5, 5);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 13, 2, 1, 1);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, 5, 5);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdOk = new QPushButton(horizontalLayoutWidget);
        cmdOk->setObjectName(QString::fromUtf8("cmdOk"));

        horizontalLayout->addWidget(cmdOk);

        cmdCancel = new QPushButton(horizontalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);


        gridLayout->addLayout(horizontalLayout, 15, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));

        gridLayout->addLayout(horizontalLayout_2, 5, 2, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtType = new QLineEdit(horizontalLayoutWidget);
        txtType->setObjectName(QString::fromUtf8("txtType"));
        txtType->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtType->sizePolicy().hasHeightForWidth());
        txtType->setSizePolicy(sizePolicy);
        txtType->setMinimumSize(QSize(200, 0));
        txtType->setReadOnly(true);

        horizontalLayout_3->addWidget(txtType);

        cmdTypeChange = new QPushButton(horizontalLayoutWidget);
        cmdTypeChange->setObjectName(QString::fromUtf8("cmdTypeChange"));

        horizontalLayout_3->addWidget(cmdTypeChange);

        chkCounterTypeManual = new QCheckBox(horizontalLayoutWidget);
        chkCounterTypeManual->setObjectName(QString::fromUtf8("chkCounterTypeManual"));

        horizontalLayout_3->addWidget(chkCounterTypeManual);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        txtNumber = new QLineEdit(horizontalLayoutWidget);
        txtNumber->setObjectName(QString::fromUtf8("txtNumber"));
        txtNumber->setMinimumSize(QSize(250, 0));
        txtNumber->setFrame(true);

        horizontalLayout_4->addWidget(txtNumber);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_4, 0, 2, 1, 1);

        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 6, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        txtAddress = new QLineEdit(horizontalLayoutWidget);
        txtAddress->setObjectName(QString::fromUtf8("txtAddress"));
        txtAddress->setMinimumSize(QSize(25, 0));
        txtAddress->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(txtAddress);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_5);

        txtDepth = new QLineEdit(horizontalLayoutWidget);
        txtDepth->setObjectName(QString::fromUtf8("txtDepth"));
        txtDepth->setMinimumSize(QSize(30, 0));
        txtDepth->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(txtDepth);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_5, 6, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_8, 14, 2, 1, 1);

        label_10 = new QLabel(horizontalLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 4, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        txtPassword = new QLineEdit(horizontalLayoutWidget);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setMinimumSize(QSize(150, 0));
        txtPassword->setMaximumSize(QSize(200, 16777215));
        txtPassword->setFrame(true);

        horizontalLayout_9->addWidget(txtPassword);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);


        gridLayout->addLayout(horizontalLayout_9, 4, 2, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        txtTimeoutRead = new QLineEdit(horizontalLayoutWidget);
        txtTimeoutRead->setObjectName(QString::fromUtf8("txtTimeoutRead"));
        txtTimeoutRead->setMinimumSize(QSize(50, 0));
        txtTimeoutRead->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_7->addWidget(txtTimeoutRead);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_7->addWidget(label_7);

        txtTimeoutWrite = new QLineEdit(horizontalLayoutWidget);
        txtTimeoutWrite->setObjectName(QString::fromUtf8("txtTimeoutWrite"));
        txtTimeoutWrite->setMinimumSize(QSize(50, 0));
        txtTimeoutWrite->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_7->addWidget(txtTimeoutWrite);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_7, 7, 2, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, 6, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        cmdAddChannel = new QPushButton(horizontalLayoutWidget);
        cmdAddChannel->setObjectName(QString::fromUtf8("cmdAddChannel"));

        verticalLayout->addWidget(cmdAddChannel);

        cmdAddParam = new QPushButton(horizontalLayoutWidget);
        cmdAddParam->setObjectName(QString::fromUtf8("cmdAddParam"));

        verticalLayout->addWidget(cmdAddParam);

        cmdRemove = new QPushButton(horizontalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_6, 12, 2, 1, 1);

        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_9, 12, 0, 1, 1);

        label_11 = new QLabel(horizontalLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 11, 0, 1, 1);

        chkAllow = new QCheckBox(horizontalLayoutWidget);
        chkAllow->setObjectName(QString::fromUtf8("chkAllow"));
        chkAllow->setChecked(true);

        gridLayout->addWidget(chkAllow, 11, 2, 1, 1);

        label_12 = new QLabel(horizontalLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        txtLogin = new QLineEdit(horizontalLayoutWidget);
        txtLogin->setObjectName(QString::fromUtf8("txtLogin"));
        txtLogin->setMinimumSize(QSize(150, 0));
        txtLogin->setMaximumSize(QSize(200, 16777215));
        txtLogin->setFrame(true);

        horizontalLayout_10->addWidget(txtLogin);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_10, 2, 2, 1, 1);

        label_14 = new QLabel(horizontalLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_14, 9, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_13 = new QLabel(horizontalLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_13);

        txtMinCorrection = new QLineEdit(horizontalLayoutWidget);
        txtMinCorrection->setObjectName(QString::fromUtf8("txtMinCorrection"));
        txtMinCorrection->setMinimumSize(QSize(25, 0));
        txtMinCorrection->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_11->addWidget(txtMinCorrection);

        label_16 = new QLabel(horizontalLayoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_16);

        txtMaxCorrection = new QLineEdit(horizontalLayoutWidget);
        txtMaxCorrection->setObjectName(QString::fromUtf8("txtMaxCorrection"));
        txtMaxCorrection->setMinimumSize(QSize(30, 0));
        txtMaxCorrection->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_11->addWidget(txtMaxCorrection);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);


        gridLayout->addLayout(horizontalLayout_11, 9, 2, 1, 1);

        label_15 = new QLabel(horizontalLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_15, 8, 0, 1, 1);

        chkTimeCorrection = new QCheckBox(horizontalLayoutWidget);
        chkTimeCorrection->setObjectName(QString::fromUtf8("chkTimeCorrection"));
        chkTimeCorrection->setChecked(true);

        gridLayout->addWidget(chkTimeCorrection, 8, 2, 1, 1);


        mainLayout->addLayout(gridLayout);

        QWidget::setTabOrder(txtNumber, cmdTypeChange);
        QWidget::setTabOrder(cmdTypeChange, txtLogin);
        QWidget::setTabOrder(txtLogin, txtPassword);
        QWidget::setTabOrder(txtPassword, txtAddress);
        QWidget::setTabOrder(txtAddress, txtDepth);
        QWidget::setTabOrder(txtDepth, txtTimeoutRead);
        QWidget::setTabOrder(txtTimeoutRead, txtTimeoutWrite);
        QWidget::setTabOrder(txtTimeoutWrite, chkAllow);
        QWidget::setTabOrder(chkAllow, cmdAddChannel);
        QWidget::setTabOrder(cmdAddChannel, cmdRemove);
        QWidget::setTabOrder(cmdRemove, cmdOk);
        QWidget::setTabOrder(cmdOk, cmdCancel);
        QWidget::setTabOrder(cmdCancel, txtType);

        retranslateUi(CounterSets);
        QObject::connect(cmdOk, SIGNAL(clicked()), CounterSets, SLOT(saveChanges()));
        QObject::connect(cmdCancel, SIGNAL(clicked()), CounterSets, SLOT(dropChanges()));
        QObject::connect(cmdTypeChange, SIGNAL(clicked()), CounterSets, SLOT(typeChangeRequest()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), CounterSets, SLOT(removeItem()));
        QObject::connect(cmdAddChannel, SIGNAL(clicked()), CounterSets, SLOT(appendChild()));
        QObject::connect(cmdAddParam, SIGNAL(clicked()), CounterSets, SLOT(addParams()));

        QMetaObject::connectSlotsByName(CounterSets);
    } // setupUi

    void retranslateUi(QWidget *CounterSets)
    {
        CounterSets->setWindowTitle(QApplication::translate("CounterSets", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CounterSets", "\320\235\320\276\320\274\320\265\321\200 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        cmdOk->setText(QApplication::translate("CounterSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("CounterSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CounterSets", "\320\242\320\270\320\277 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        cmdTypeChange->setText(QApplication::translate("CounterSets", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214...", 0, QApplication::UnicodeUTF8));
        chkCounterTypeManual->setText(QApplication::translate("CounterSets", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\262\321\200\321\203\321\207\320\275\321\203\321\216", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CounterSets", "\320\220\320\264\321\200\320\265\321\201:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CounterSets", "\320\223\320\273\321\203\320\261\320\270\320\275\320\260 \321\207\321\202\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        txtDepth->setText(QApplication::translate("CounterSets", "10", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("CounterSets", "\320\237\320\260\321\200\320\276\320\273\321\214", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("CounterSets", "\320\247\321\202\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        txtTimeoutRead->setText(QApplication::translate("CounterSets", "2500", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("CounterSets", "\320\227\320\260\320\277\320\270\321\201\320\270:", 0, QApplication::UnicodeUTF8));
        txtTimeoutWrite->setText(QApplication::translate("CounterSets", "1000", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CounterSets", "\320\242\320\260\320\271\320\274\320\260\321\203\321\202\321\213:", 0, QApplication::UnicodeUTF8));
        cmdAddChannel->setText(QApplication::translate("CounterSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        cmdAddParam->setText(QApplication::translate("CounterSets", "\320\224\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213...", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("CounterSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("CounterSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("CounterSets", "\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214 \320\276\320\277\321\200\320\276\321\201:", 0, QApplication::UnicodeUTF8));
        chkAllow->setText(QString());
        label_12->setText(QApplication::translate("CounterSets", "\320\233\320\276\320\263\320\270\320\275:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QString());
        label_13->setText(QApplication::translate("CounterSets", "\320\224\320\270\320\260\320\277\320\260\320\267\320\276\320\275 \320\272\320\276\321\200\321\200\320\265\320\272\321\206\320\270\320\270 \320\262\321\200\320\265\320\274\320\265\320\275\320\270 (\321\201\320\265\320\272.):", 0, QApplication::UnicodeUTF8));
        txtMinCorrection->setText(QApplication::translate("CounterSets", "2", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("CounterSets", "-", 0, QApplication::UnicodeUTF8));
        txtMaxCorrection->setText(QApplication::translate("CounterSets", "10", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("CounterSets", "\320\232\320\276\321\200\321\200. \320\262\321\200\320\265\320\274\320\265\320\275\320\270:", 0, QApplication::UnicodeUTF8));
        chkTimeCorrection->setText(QApplication::translate("CounterSets", "\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214 \320\272\320\276\321\200\321\200\320\265\320\272\321\202\320\270\321\200\320\276\320\262\320\272\321\203 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CounterSets: public Ui_CounterSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERSETS_H
