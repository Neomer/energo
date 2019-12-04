/********************************************************************************
** Form generated from reading UI file 'ScheduleSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULESETS_H
#define UI_SCHEDULESETS_H

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
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleSets
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtShift;
    QComboBox *cmbShift;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtPeriod;
    QComboBox *cmbPeriod;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cmdSave;
    QPushButton *cmdCancel;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *lstObj;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cmdAdd;
    QPushButton *cmdRemove;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdRemoveSchedule;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *txtStartTime;
    QLabel *label_7;
    QLineEdit *txtEndTime;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *ScheduleSets)
    {
        if (ScheduleSets->objectName().isEmpty())
            ScheduleSets->setObjectName(QString::fromUtf8("ScheduleSets"));
        ScheduleSets->resize(661, 638);
        verticalLayoutWidget = new QWidget(ScheduleSets);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 460, 358));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtShift = new QLineEdit(verticalLayoutWidget);
        txtShift->setObjectName(QString::fromUtf8("txtShift"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtShift->sizePolicy().hasHeightForWidth());
        txtShift->setSizePolicy(sizePolicy);
        txtShift->setMinimumSize(QSize(50, 0));
        txtShift->setMaximumSize(QSize(50, 16777215));
        txtShift->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(txtShift);

        cmbShift = new QComboBox(verticalLayoutWidget);
        cmbShift->setObjectName(QString::fromUtf8("cmbShift"));
        sizePolicy.setHeightForWidth(cmbShift->sizePolicy().hasHeightForWidth());
        cmbShift->setSizePolicy(sizePolicy);
        cmbShift->setMinimumSize(QSize(100, 0));
        cmbShift->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(cmbShift);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtName = new QLineEdit(verticalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(268, 0));

        horizontalLayout->addWidget(txtName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtPeriod = new QLineEdit(verticalLayoutWidget);
        txtPeriod->setObjectName(QString::fromUtf8("txtPeriod"));
        sizePolicy.setHeightForWidth(txtPeriod->sizePolicy().hasHeightForWidth());
        txtPeriod->setSizePolicy(sizePolicy);
        txtPeriod->setMinimumSize(QSize(50, 0));
        txtPeriod->setMaximumSize(QSize(50, 16777215));
        txtPeriod->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(txtPeriod);

        cmbPeriod = new QComboBox(verticalLayoutWidget);
        cmbPeriod->setObjectName(QString::fromUtf8("cmbPeriod"));
        sizePolicy.setHeightForWidth(cmbPeriod->sizePolicy().hasHeightForWidth());
        cmbPeriod->setSizePolicy(sizePolicy);
        cmbPeriod->setMinimumSize(QSize(100, 0));
        cmbPeriod->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(cmbPeriod);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

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


        gridLayout->addLayout(horizontalLayout_4, 7, 1, 1, 1);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_4, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        lstObj = new QTableWidget(verticalLayoutWidget);
        lstObj->setObjectName(QString::fromUtf8("lstObj"));
        lstObj->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstObj->setSelectionMode(QAbstractItemView::ExtendedSelection);
        lstObj->setSelectionBehavior(QAbstractItemView::SelectRows);
        lstObj->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_5->addWidget(lstObj);

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


        gridLayout->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_5, 6, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cmdRemoveSchedule = new QPushButton(verticalLayoutWidget);
        cmdRemoveSchedule->setObjectName(QString::fromUtf8("cmdRemoveSchedule"));

        verticalLayout->addWidget(cmdRemoveSchedule);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        gridLayout->addLayout(horizontalLayout_6, 6, 1, 1, 1);

        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        txtStartTime = new QLineEdit(verticalLayoutWidget);
        txtStartTime->setObjectName(QString::fromUtf8("txtStartTime"));
        sizePolicy.setHeightForWidth(txtStartTime->sizePolicy().hasHeightForWidth());
        txtStartTime->setSizePolicy(sizePolicy);
        txtStartTime->setMinimumSize(QSize(100, 0));
        txtStartTime->setMaximumSize(QSize(50, 16777215));
        txtStartTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(txtStartTime);

        label_7 = new QLabel(verticalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_7);

        txtEndTime = new QLineEdit(verticalLayoutWidget);
        txtEndTime->setObjectName(QString::fromUtf8("txtEndTime"));
        sizePolicy.setHeightForWidth(txtEndTime->sizePolicy().hasHeightForWidth());
        txtEndTime->setSizePolicy(sizePolicy);
        txtEndTime->setMinimumSize(QSize(100, 0));
        txtEndTime->setMaximumSize(QSize(50, 16777215));
        txtEndTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(txtEndTime);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_7, 3, 1, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(ScheduleSets);
        QObject::connect(cmdSave, SIGNAL(clicked()), ScheduleSets, SLOT(saveChanges()));
        QObject::connect(cmdCancel, SIGNAL(clicked()), ScheduleSets, SLOT(dropChanges()));
        QObject::connect(cmdAdd, SIGNAL(clicked()), ScheduleSets, SLOT(appendObjects()));
        QObject::connect(txtPeriod, SIGNAL(textChanged(QString)), ScheduleSets, SLOT(periodChanged(QString)));
        QObject::connect(txtShift, SIGNAL(textChanged(QString)), ScheduleSets, SLOT(shiftChanged(QString)));
        QObject::connect(cmdRemove, SIGNAL(clicked()), ScheduleSets, SLOT(removeObjects()));
        QObject::connect(cmdRemoveSchedule, SIGNAL(clicked()), ScheduleSets, SLOT(onRemove()));

        QMetaObject::connectSlotsByName(ScheduleSets);
    } // setupUi

    void retranslateUi(QWidget *ScheduleSets)
    {
        ScheduleSets->setWindowTitle(QApplication::translate("ScheduleSets", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ScheduleSets", "\320\237\320\265\321\200\320\270\320\276\320\264\320\270\321\207\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ScheduleSets", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ScheduleSets", "\320\227\320\260\320\264\320\265\321\200\320\266\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("ScheduleSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("ScheduleSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ScheduleSets", "\320\236\320\261\321\212\320\265\320\272\321\202\321\213:", 0, QApplication::UnicodeUTF8));
        cmdAdd->setText(QApplication::translate("ScheduleSets", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("ScheduleSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ScheduleSets", "\320\224\320\265\320\271\321\201\321\202\320\262\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        cmdRemoveSchedule->setText(QApplication::translate("ScheduleSets", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("ScheduleSets", "\320\224\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276\320\265 \320\262\321\200\320\265\320\274\321\217:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ScheduleSets", "-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScheduleSets: public Ui_ScheduleSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULESETS_H
