/********************************************************************************
** Form generated from reading UI file 'DataViewForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAVIEWFORM_H
#define UI_DATAVIEWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
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

class Ui_DataViewForm
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QTreeWidget *twObjects;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDateTimeEdit *dteBegin;
    QLabel *label_2;
    QDateTimeEdit *dteEnd;
    QComboBox *cmbItvType;
    QLabel *label_3;
    QComboBox *cmbItvLength;
    QPushButton *cmdRefresh;
    QPushButton *cmdExcel;
    QSpacerItem *horizontalSpacer;
    QTableWidget *twData;
    QGraphicsView *gvGraph;

    void setupUi(QWidget *DataViewForm)
    {
        if (DataViewForm->objectName().isEmpty())
            DataViewForm->setObjectName(QString::fromUtf8("DataViewForm"));
        DataViewForm->resize(872, 576);
        verticalLayoutWidget = new QWidget(DataViewForm);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 897, 561));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        twObjects = new QTreeWidget(verticalLayoutWidget);
        twObjects->setObjectName(QString::fromUtf8("twObjects"));

        gridLayout->addWidget(twObjects, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(4, 0, 4, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 2);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        dteBegin = new QDateTimeEdit(verticalLayoutWidget);
        dteBegin->setObjectName(QString::fromUtf8("dteBegin"));
        dteBegin->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout->addWidget(dteBegin);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        dteEnd = new QDateTimeEdit(verticalLayoutWidget);
        dteEnd->setObjectName(QString::fromUtf8("dteEnd"));
        dteEnd->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout->addWidget(dteEnd);

        cmbItvType = new QComboBox(verticalLayoutWidget);
        cmbItvType->setObjectName(QString::fromUtf8("cmbItvType"));
        cmbItvType->setMinimumSize(QSize(100, 0));
        cmbItvType->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

        horizontalLayout->addWidget(cmbItvType);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        cmbItvLength = new QComboBox(verticalLayoutWidget);
        cmbItvLength->setObjectName(QString::fromUtf8("cmbItvLength"));
        cmbItvLength->setMinimumSize(QSize(120, 0));

        horizontalLayout->addWidget(cmbItvLength);

        cmdRefresh = new QPushButton(verticalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/viewdlg/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);
        cmdRefresh->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdRefresh);

        cmdExcel = new QPushButton(verticalLayoutWidget);
        cmdExcel->setObjectName(QString::fromUtf8("cmdExcel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/viewdlg/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdExcel->setIcon(icon1);
        cmdExcel->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdExcel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        twData = new QTableWidget(verticalLayoutWidget);
        twData->setObjectName(QString::fromUtf8("twData"));
        twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twData->horizontalHeader()->setHighlightSections(false);
        twData->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(twData);

        gvGraph = new QGraphicsView(verticalLayoutWidget);
        gvGraph->setObjectName(QString::fromUtf8("gvGraph"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gvGraph->sizePolicy().hasHeightForWidth());
        gvGraph->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(gvGraph);

        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(1, 50);

        mainLayout->addLayout(gridLayout);


        retranslateUi(DataViewForm);

        cmbItvType->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DataViewForm);
    } // setupUi

    void retranslateUi(QWidget *DataViewForm)
    {
        DataViewForm->setWindowTitle(QApplication::translate("DataViewForm", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twObjects->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("DataViewForm", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DataViewForm", "\320\235\320\260\321\207\320\260\320\273\320\276:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DataViewForm", "\320\232\320\276\320\275\320\265\321\206:", 0, QApplication::UnicodeUTF8));
        cmbItvType->clear();
        cmbItvType->insertItems(0, QStringList()
         << QApplication::translate("DataViewForm", "\320\227\320\260\320\264\320\260\321\202\321\214...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataViewForm", "\320\241\321\203\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataViewForm", "\320\235\320\265\320\264\320\265\320\273\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("DataViewForm", "\320\234\320\265\321\201\321\217\321\206", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("DataViewForm", "\320\222\321\200\320\265\320\274\321\217 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cmdRefresh->setToolTip(QApplication::translate("DataViewForm", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdRefresh->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdExcel->setToolTip(QApplication::translate("DataViewForm", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 MS Excel...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdExcel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataViewForm: public Ui_DataViewForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAVIEWFORM_H
