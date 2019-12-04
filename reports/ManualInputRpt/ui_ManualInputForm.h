/********************************************************************************
** Form generated from reading UI file 'ManualInputForm.ui'
**
** Created: Tue 23. Jul 15:19:44 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALINPUTFORM_H
#define UI_MANUALINPUTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
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

class Ui_Form
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *twObjects;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QDateTimeEdit *dteBegin;
    QLabel *label_3;
    QDateTimeEdit *dteEnd;
    QComboBox *cmbItvType;
    QLabel *label_4;
    QComboBox *cmbCounterType;
    QPushButton *cmdRefresh;
    QPushButton *cmdSave;
    QSpacerItem *horizontalSpacer;
    QTableWidget *twData;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(678, 509);
        verticalLayoutWidget = new QWidget(Form);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 840, 481));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        twObjects = new QTreeWidget(verticalLayoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        twObjects->setHeaderItem(__qtreewidgetitem);
        twObjects->setObjectName(QString::fromUtf8("twObjects"));
        twObjects->header()->setVisible(false);

        horizontalLayout->addWidget(twObjects);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        dteBegin = new QDateTimeEdit(verticalLayoutWidget);
        dteBegin->setObjectName(QString::fromUtf8("dteBegin"));
        dteBegin->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout_2->addWidget(dteBegin);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        dteEnd = new QDateTimeEdit(verticalLayoutWidget);
        dteEnd->setObjectName(QString::fromUtf8("dteEnd"));
        dteEnd->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout_2->addWidget(dteEnd);

        cmbItvType = new QComboBox(verticalLayoutWidget);
        cmbItvType->setObjectName(QString::fromUtf8("cmbItvType"));
        cmbItvType->setMinimumSize(QSize(100, 0));
        cmbItvType->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

        horizontalLayout_2->addWidget(cmbItvType);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        cmbCounterType = new QComboBox(verticalLayoutWidget);
        cmbCounterType->setObjectName(QString::fromUtf8("cmbCounterType"));
        cmbCounterType->setMinimumSize(QSize(100, 0));
        cmbCounterType->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

        horizontalLayout_2->addWidget(cmbCounterType);

        cmdRefresh = new QPushButton(verticalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/manualinput/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);
        cmdRefresh->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(cmdRefresh);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/manualinput/images/database-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdSave->setIcon(icon1);
        cmdSave->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(cmdSave);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        twData = new QTableWidget(verticalLayoutWidget);
        twData->setObjectName(QString::fromUtf8("twData"));

        verticalLayout->addWidget(twData);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(1, 1);

        mainLayout->addLayout(horizontalLayout);


        retranslateUi(Form);

        cmbItvType->setCurrentIndex(1);
        cmbCounterType->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("Form", "\320\235\320\260\321\207\320\260\320\273\320\276:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Form", "\320\232\320\276\320\275\320\265\321\206:", 0, QApplication::UnicodeUTF8));
        cmbItvType->clear();
        cmbItvType->insertItems(0, QStringList()
         << QApplication::translate("Form", "\320\227\320\260\320\264\320\260\321\202\321\214...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\320\241\321\203\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\320\235\320\265\320\264\320\265\320\273\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\320\234\320\265\321\201\321\217\321\206", 0, QApplication::UnicodeUTF8)
        );
        label_4->setText(QApplication::translate("Form", "\320\236\321\202\321\204\320\270\320\273\321\214\321\202\321\200\320\276\320\262\320\260\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        cmbCounterType->clear();
        cmbCounterType->insertItems(0, QStringList()
         << QApplication::translate("Form", "\320\222\321\201\320\265", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Form", "\320\240\321\203\321\207\320\275\320\276\320\271 \320\262\320\262\320\276\320\264", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        cmdRefresh->setToolTip(QApplication::translate("Form", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdRefresh->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdSave->setToolTip(QApplication::translate("Form", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdSave->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ManualInputForm: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALINPUTFORM_H
