/********************************************************************************
** Form generated from reading UI file 'CounterAddParamSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTERADDPARAMSETS_H
#define UI_COUNTERADDPARAMSETS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CounterAddParamSets
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *twParams;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSave;
    QPushButton *cmdCancel;

    void setupUi(QDialog *CounterAddParamSets)
    {
        if (CounterAddParamSets->objectName().isEmpty())
            CounterAddParamSets->setObjectName(QString::fromUtf8("CounterAddParamSets"));
        CounterAddParamSets->resize(643, 524);
        verticalLayoutWidget = new QWidget(CounterAddParamSets);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 10, 551, 461));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        twParams = new QTableWidget(verticalLayoutWidget);
        twParams->setObjectName(QString::fromUtf8("twParams"));
        twParams->setSelectionMode(QAbstractItemView::SingleSelection);
        twParams->horizontalHeader()->setDefaultSectionSize(200);
        twParams->horizontalHeader()->setHighlightSections(false);
        twParams->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_2->addWidget(twParams);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 6, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout->addWidget(cmdSave);

        cmdCancel = new QPushButton(verticalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);


        verticalLayout_2->addLayout(horizontalLayout);


        mainLayout->addLayout(verticalLayout_2);


        retranslateUi(CounterAddParamSets);
        QObject::connect(cmdCancel, SIGNAL(clicked()), CounterAddParamSets, SLOT(reject()));
        QObject::connect(cmdSave, SIGNAL(clicked()), CounterAddParamSets, SLOT(saveChanges()));

        QMetaObject::connectSlotsByName(CounterAddParamSets);
    } // setupUi

    void retranslateUi(QDialog *CounterAddParamSets)
    {
        CounterAddParamSets->setWindowTitle(QApplication::translate("CounterAddParamSets", "Dialog", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("CounterAddParamSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("CounterAddParamSets", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CounterAddParamSets: public Ui_CounterAddParamSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTERADDPARAMSETS_H
