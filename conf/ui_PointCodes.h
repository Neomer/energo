/********************************************************************************
** Form generated from reading UI file 'PointCodes.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POINTCODES_H
#define UI_POINTCODES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
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

class Ui_PointCodes
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cmbModel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *txtCode;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QPushButton *cmdAdd;
    QPushButton *cmdEdit;
    QPushButton *cmdRemove;
    QSpacerItem *verticalSpacer;
    QTableWidget *twCodes;

    void setupUi(QDialog *PointCodes)
    {
        if (PointCodes->objectName().isEmpty())
            PointCodes->setObjectName(QString::fromUtf8("PointCodes"));
        PointCodes->resize(584, 499);
        verticalLayoutWidget = new QWidget(PointCodes);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 20, 541, 441));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(6, 6, 6, 20);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmbModel = new QComboBox(verticalLayoutWidget);
        cmbModel->setObjectName(QString::fromUtf8("cmbModel"));
        cmbModel->setMinimumSize(QSize(200, 0));

        horizontalLayout_3->addWidget(cmbModel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        txtCode = new QLineEdit(verticalLayoutWidget);
        txtCode->setObjectName(QString::fromUtf8("txtCode"));

        gridLayout->addWidget(txtCode, 1, 1, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, -1, -1, -1);
        cmdAdd = new QPushButton(verticalLayoutWidget);
        cmdAdd->setObjectName(QString::fromUtf8("cmdAdd"));

        verticalLayout->addWidget(cmdAdd);

        cmdEdit = new QPushButton(verticalLayoutWidget);
        cmdEdit->setObjectName(QString::fromUtf8("cmdEdit"));

        verticalLayout->addWidget(cmdEdit);

        cmdRemove = new QPushButton(verticalLayoutWidget);
        cmdRemove->setObjectName(QString::fromUtf8("cmdRemove"));

        verticalLayout->addWidget(cmdRemove);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 2, 2, 1, 1);

        twCodes = new QTableWidget(verticalLayoutWidget);
        twCodes->setObjectName(QString::fromUtf8("twCodes"));
        twCodes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twCodes->setSelectionMode(QAbstractItemView::SingleSelection);
        twCodes->setSelectionBehavior(QAbstractItemView::SelectRows);
        twCodes->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        twCodes->horizontalHeader()->setCascadingSectionResizes(true);
        twCodes->horizontalHeader()->setMinimumSectionSize(20);
        twCodes->horizontalHeader()->setStretchLastSection(true);
        twCodes->verticalHeader()->setDefaultSectionSize(20);

        gridLayout->addWidget(twCodes, 2, 1, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(PointCodes);
        QObject::connect(cmdAdd, SIGNAL(clicked()), PointCodes, SLOT(onAddClick()));
        QObject::connect(cmdEdit, SIGNAL(clicked()), PointCodes, SLOT(onEditClick()));
        QObject::connect(cmdRemove, SIGNAL(clicked()), PointCodes, SLOT(onRemoveClick()));
        QObject::connect(twCodes, SIGNAL(itemClicked(QTableWidgetItem*)), PointCodes, SLOT(onElementSelect(QTableWidgetItem*)));

        QMetaObject::connectSlotsByName(PointCodes);
    } // setupUi

    void retranslateUi(QDialog *PointCodes)
    {
        PointCodes->setWindowTitle(QApplication::translate("PointCodes", "Dialog", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PointCodes", "\320\232\320\276\320\264:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PointCodes", "\320\234\320\260\320\272\320\265\321\202:", 0, QApplication::UnicodeUTF8));
        cmdAdd->setText(QApplication::translate("PointCodes", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdEdit->setText(QApplication::translate("PointCodes", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdRemove->setText(QApplication::translate("PointCodes", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PointCodes: public Ui_PointCodes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POINTCODES_H
