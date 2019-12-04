/********************************************************************************
** Form generated from reading UI file 'AlertViewForm.ui'
**
** Created: Thu 4. Oct 10:48:42 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTVIEWFORM_H
#define UI_ALERTVIEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlertViewForm
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *twAlerts;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *cmbSince;
    QLabel *label_2;
    QComboBox *cmbLevel;
    QPushButton *cmdRefresh;
    QSpacerItem *horizontalSpacer;
    QTableWidget *twList;

    void setupUi(QWidget *AlertViewForm)
    {
        if (AlertViewForm->objectName().isEmpty())
            AlertViewForm->setObjectName(QString::fromUtf8("AlertViewForm"));
        AlertViewForm->resize(878, 607);
        horizontalLayoutWidget = new QWidget(AlertViewForm);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 801, 581));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        twAlerts = new QTreeWidget(horizontalLayoutWidget);
        twAlerts->setObjectName(QString::fromUtf8("twAlerts"));
        twAlerts->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        twAlerts->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twAlerts->setProperty("showDropIndicator", QVariant(false));
        twAlerts->setItemsExpandable(false);
        twAlerts->header()->setVisible(true);
        twAlerts->header()->setDefaultSectionSize(170);
        twAlerts->header()->setHighlightSections(true);
        twAlerts->header()->setMinimumSectionSize(10);

        horizontalLayout->addWidget(twAlerts);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, -1, -1);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        cmbSince = new QComboBox(horizontalLayoutWidget);
        cmbSince->setObjectName(QString::fromUtf8("cmbSince"));
        cmbSince->setMinimumSize(QSize(160, 0));

        horizontalLayout_2->addWidget(cmbSince);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cmbLevel = new QComboBox(horizontalLayoutWidget);
        cmbLevel->setObjectName(QString::fromUtf8("cmbLevel"));
        cmbLevel->setMinimumSize(QSize(160, 0));

        horizontalLayout_2->addWidget(cmbLevel);

        cmdRefresh = new QPushButton(horizontalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/AlertView/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);

        horizontalLayout_2->addWidget(cmdRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        twList = new QTableWidget(horizontalLayoutWidget);
        twList->setObjectName(QString::fromUtf8("twList"));
        twList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twList->setSelectionMode(QAbstractItemView::SingleSelection);
        twList->setSelectionBehavior(QAbstractItemView::SelectRows);
        twList->horizontalHeader()->setHighlightSections(false);
        twList->horizontalHeader()->setStretchLastSection(true);
        twList->verticalHeader()->setDefaultSectionSize(20);
        twList->verticalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(twList);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(1, 1);

        mainLayout->addLayout(horizontalLayout);


        retranslateUi(AlertViewForm);

        QMetaObject::connectSlotsByName(AlertViewForm);
    } // setupUi

    void retranslateUi(QWidget *AlertViewForm)
    {
        AlertViewForm->setWindowTitle(QApplication::translate("AlertViewForm", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twAlerts->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("AlertViewForm", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("AlertViewForm", "\320\242\320\270\320\277 \321\201\320\276\320\261\321\213\321\202\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AlertViewForm", "\320\241\321\200\320\276\320\272 \320\264\320\260\320\262\320\275\320\276\321\201\321\202\320\270:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AlertViewForm", "\320\222\320\260\320\266\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        cmdRefresh->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AlertViewForm: public Ui_AlertViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTVIEWFORM_H
