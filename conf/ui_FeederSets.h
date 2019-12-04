/********************************************************************************
** Form generated from reading UI file 'FeederSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEEDERSETS_H
#define UI_FEEDERSETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
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

class Ui_FeederSets
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cmdSave;
    QPushButton *cmdDrop;
    QLabel *label_8;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAddCounter;
    QPushButton *cmdRemove;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *txtKTh;
    QLabel *label_5;
    QLineEdit *txtKTl;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *txtKNh;
    QLabel *label_7;
    QLineEdit *txtKNl;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *cmbVoltageLVL;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QPushButton *cmdChangeTrans;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QWidget *FeederSets)
    {
        if (FeederSets->objectName().isEmpty())
            FeederSets->setObjectName(QString::fromUtf8("FeederSets"));
        FeederSets->resize(559, 564);
        horizontalLayoutWidget = new QWidget(FeederSets);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 541, 541));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(10, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 5, -1, -1);
        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        verticalLayout_3->addWidget(label_3);


        gridLayout->addLayout(verticalLayout_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtName = new QLineEdit(horizontalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(100, 0));
        txtName->setMaximumSize(QSize(450, 16777215));

        horizontalLayout->addWidget(txtName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 5, 5, 5);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cmdSave = new QPushButton(horizontalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_2->addWidget(cmdSave);

        cmdDrop = new QPushButton(horizontalLayoutWidget);
        cmdDrop->setObjectName(QString::fromUtf8("cmdDrop"));

        horizontalLayout_2->addWidget(cmdDrop);


        gridLayout->addLayout(horizontalLayout_2, 9, 2, 1, 1);

        label_8 = new QLabel(horizontalLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 0, 1, 1);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 5, -1);
        cmdAddCounter = new QPushButton(horizontalLayoutWidget);
        cmdAddCounter->setObjectName(QString::fromUtf8("cmdAddCounter"));
        cmdAddCounter->setEnabled(true);

        verticalLayout->addWidget(cmdAddCounter);

        cmdRemove = new QPushButton(horizontalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 6, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, 5, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 15, -1);
        label_4 = new QLabel(horizontalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        txtKTh = new QLineEdit(horizontalLayoutWidget);
        txtKTh->setObjectName(QString::fromUtf8("txtKTh"));
        txtKTh->setMinimumSize(QSize(50, 0));
        txtKTh->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_5->addWidget(txtKTh);

        label_5 = new QLabel(horizontalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        txtKTl = new QLineEdit(horizontalLayoutWidget);
        txtKTl->setObjectName(QString::fromUtf8("txtKTl"));
        txtKTl->setMinimumSize(QSize(50, 0));
        txtKTl->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_5->addWidget(txtKTl);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, 15, -1);
        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        txtKNh = new QLineEdit(horizontalLayoutWidget);
        txtKNh->setObjectName(QString::fromUtf8("txtKNh"));
        txtKNh->setMinimumSize(QSize(50, 0));
        txtKNh->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(txtKNh);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_6->addWidget(label_7);

        txtKNl = new QLineEdit(horizontalLayoutWidget);
        txtKNl->setObjectName(QString::fromUtf8("txtKNl"));
        txtKNl->setMinimumSize(QSize(50, 0));
        txtKNl->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(txtKNl);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_4, 2, 2, 1, 1);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_2, 6, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        cmbVoltageLVL = new QComboBox(horizontalLayoutWidget);
        cmbVoltageLVL->setObjectName(QString::fromUtf8("cmbVoltageLVL"));
        cmbVoltageLVL->setEditable(false);

        horizontalLayout_7->addWidget(cmbVoltageLVL);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        gridLayout->addLayout(horizontalLayout_7, 4, 2, 1, 1);

        label_9 = new QLabel(horizontalLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, 6, -1);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, -1, 6, -1);
        cmdChangeTrans = new QPushButton(horizontalLayoutWidget);
        cmdChangeTrans->setObjectName(QString::fromUtf8("cmdChangeTrans"));

        verticalLayout_5->addWidget(cmdChangeTrans);


        horizontalLayout_8->addLayout(verticalLayout_5);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_8, 5, 2, 1, 1);


        mainLayout->addLayout(gridLayout);

        QWidget::setTabOrder(txtName, txtKTh);
        QWidget::setTabOrder(txtKTh, txtKTl);
        QWidget::setTabOrder(txtKTl, txtKNh);
        QWidget::setTabOrder(txtKNh, txtKNl);
        QWidget::setTabOrder(txtKNl, cmdAddCounter);
        QWidget::setTabOrder(cmdAddCounter, cmdRemove);
        QWidget::setTabOrder(cmdRemove, cmdSave);
        QWidget::setTabOrder(cmdSave, cmdDrop);

        retranslateUi(FeederSets);
        QObject::connect(cmdSave, SIGNAL(clicked()), FeederSets, SLOT(saveChanges()));
        QObject::connect(cmdDrop, SIGNAL(clicked()), FeederSets, SLOT(dropChanges()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), FeederSets, SLOT(removeFeeder()));
        QObject::connect(cmdAddCounter, SIGNAL(clicked()), FeederSets, SLOT(appendChild()));

        QMetaObject::connectSlotsByName(FeederSets);
    } // setupUi

    void retranslateUi(QWidget *FeederSets)
    {
        FeederSets->setWindowTitle(QApplication::translate("FeederSets", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("FeederSets", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202\321\213 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\206\320\270\320\270", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("FeederSets", "\320\232\320\242:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("FeederSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdDrop->setText(QApplication::translate("FeederSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FeederSets", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FeederSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        cmdAddCounter->setText(QApplication::translate("FeederSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\321\207\320\265\321\202\321\207\320\270\320\272", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("FeederSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("FeederSets", "\320\232\320\242\320\242", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FeederSets", "/", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FeederSets", "\320\232\320\242\320\235", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FeederSets", "/", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FeederSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FeederSets", "\320\236\320\277\320\265\321\200\320\260\321\206\320\270\320\270:", 0, QApplication::UnicodeUTF8));
        cmdChangeTrans->setText(QApplication::translate("FeederSets", "\320\227\320\260\320\274\320\265\320\275\320\260 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FeederSets: public Ui_FeederSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEEDERSETS_H
