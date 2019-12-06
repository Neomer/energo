/********************************************************************************
** Form generated from reading UI file 'balansrptform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANSRPTFORM_H
#define UI_BALANSRPTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalansRptForm
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
    QComboBox *cmbValueRound;
    QLabel *label_3;
    QSpinBox *txtAccuracy;
    QPushButton *cmdRefresh;
    QPushButton *cmdExcel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *cmbGroupType;
    QCheckBox *chkGeneration;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cmdFilter;
    QLabel *lblCGH;
    QComboBox *cmbControHourGroup;
    QComboBox *cmbHoly;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *twData;
    QGraphicsView *gvGraph;

    void setupUi(QWidget *BalansRptForm)
    {
        if (BalansRptForm->objectName().isEmpty())
            BalansRptForm->setObjectName(QString::fromUtf8("BalansRptForm"));
        BalansRptForm->resize(1068, 580);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BalansRptForm->sizePolicy().hasHeightForWidth());
        BalansRptForm->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(BalansRptForm);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 1051, 561));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        twObjects = new QTreeWidget(verticalLayoutWidget);
        twObjects->setObjectName(QString::fromUtf8("twObjects"));
        twObjects->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

        cmbValueRound = new QComboBox(verticalLayoutWidget);
        cmbValueRound->setObjectName(QString::fromUtf8("cmbValueRound"));
        cmbValueRound->setMinimumSize(QSize(75, 0));
        cmbValueRound->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

        horizontalLayout->addWidget(cmbValueRound);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        txtAccuracy = new QSpinBox(verticalLayoutWidget);
        txtAccuracy->setObjectName(QString::fromUtf8("txtAccuracy"));
        txtAccuracy->setMinimum(-1);
        txtAccuracy->setMaximum(6);
        txtAccuracy->setValue(3);

        horizontalLayout->addWidget(txtAccuracy);

        cmdRefresh = new QPushButton(verticalLayoutWidget);
        cmdRefresh->setObjectName(QString::fromUtf8("cmdRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/balansrpt/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);
        cmdRefresh->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdRefresh);

        cmdExcel = new QPushButton(verticalLayoutWidget);
        cmdExcel->setObjectName(QString::fromUtf8("cmdExcel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/balansrpt/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdExcel->setIcon(icon1);
        cmdExcel->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdExcel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        cmbGroupType = new QComboBox(verticalLayoutWidget);
        cmbGroupType->setObjectName(QString::fromUtf8("cmbGroupType"));
        cmbGroupType->setMinimumSize(QSize(100, 0));
        cmbGroupType->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);

        horizontalLayout_2->addWidget(cmbGroupType);

        chkGeneration = new QCheckBox(verticalLayoutWidget);
        chkGeneration->setObjectName(QString::fromUtf8("chkGeneration"));

        horizontalLayout_2->addWidget(chkGeneration);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmdFilter = new QPushButton(verticalLayoutWidget);
        cmdFilter->setObjectName(QString::fromUtf8("cmdFilter"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/balansrpt/images/filter.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdFilter->setIcon(icon2);
        cmdFilter->setCheckable(true);

        horizontalLayout_3->addWidget(cmdFilter);

        lblCGH = new QLabel(verticalLayoutWidget);
        lblCGH->setObjectName(QString::fromUtf8("lblCGH"));

        horizontalLayout_3->addWidget(lblCGH);

        cmbControHourGroup = new QComboBox(verticalLayoutWidget);
        cmbControHourGroup->setObjectName(QString::fromUtf8("cmbControHourGroup"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cmbControHourGroup->sizePolicy().hasHeightForWidth());
        cmbControHourGroup->setSizePolicy(sizePolicy1);
        cmbControHourGroup->setMinimumSize(QSize(200, 0));
        cmbControHourGroup->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(cmbControHourGroup);

        cmbHoly = new QComboBox(verticalLayoutWidget);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/balansrpt/images/all-days.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbHoly->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/balansrpt/images/work-day.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbHoly->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/balansrpt/images/weekend.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbHoly->addItem(icon5, QString());
        cmbHoly->setObjectName(QString::fromUtf8("cmbHoly"));
        cmbHoly->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(cmbHoly);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        twData = new QTableWidget(verticalLayoutWidget);
        twData->setObjectName(QString::fromUtf8("twData"));
        twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twData->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(twData);

        gvGraph = new QGraphicsView(verticalLayoutWidget);
        gvGraph->setObjectName(QString::fromUtf8("gvGraph"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(gvGraph->sizePolicy().hasHeightForWidth());
        gvGraph->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(gvGraph);

        verticalLayout->setStretch(3, 3);

        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(1, 50);

        mainLayout->addLayout(gridLayout);


        retranslateUi(BalansRptForm);

        cmbItvType->setCurrentIndex(1);
        cmbValueRound->setCurrentIndex(-1);
        cmbGroupType->setCurrentIndex(0);
        cmbControHourGroup->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(BalansRptForm);
    } // setupUi

    void retranslateUi(QWidget *BalansRptForm)
    {
        BalansRptForm->setWindowTitle(QApplication::translate("BalansRptForm", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twObjects->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("BalansRptForm", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("BalansRptForm", "\320\235\320\260\321\207\320\260\320\273\320\276:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("BalansRptForm", "\320\232\320\276\320\275\320\265\321\206:", 0, QApplication::UnicodeUTF8));
        cmbItvType->clear();
        cmbItvType->insertItems(0, QStringList()
         << QApplication::translate("BalansRptForm", "\320\227\320\260\320\264\320\260\321\202\321\214...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("BalansRptForm", "\320\241\321\203\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("BalansRptForm", "\320\235\320\265\320\264\320\265\320\273\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("BalansRptForm", "\320\234\320\265\321\201\321\217\321\206", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("BalansRptForm", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtAccuracy->setToolTip(QApplication::translate("BalansRptForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\232\320\276\320\273-\320\262\320\276 \320\267\320\275\320\260\320\272\320\276\320\262 \320\277\320\276\321\201\320\273\320\265 \320\267\320\260\320\277\321\217\321\202\320\276\320\271.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\320\265 -1, \320\264\320\273\321\217 \320\262\321\213\320\262\320\276\320\264\320\260 \320\264\320\260\320\275\320\275\321\213\321\205"
                        " &quot;\320\272\320\260\320\272 \320\265\321\201\321\202\321\214&quot;.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdRefresh->setToolTip(QApplication::translate("BalansRptForm", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdRefresh->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdExcel->setToolTip(QApplication::translate("BalansRptForm", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 MS Excel...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdExcel->setText(QString());
        label_4->setText(QApplication::translate("BalansRptForm", "\320\223\321\200\321\203\320\277\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214:", 0, QApplication::UnicodeUTF8));
        cmbGroupType->clear();
        cmbGroupType->insertItems(0, QStringList()
         << QApplication::translate("BalansRptForm", "30 \320\274\320\270\320\275\321\203\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("BalansRptForm", "60 \320\274\320\270\320\275\321\203\321\202", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("BalansRptForm", "\320\241\321\203\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8)
        );
        chkGeneration->setText(QApplication::translate("BalansRptForm", "\320\240\320\260\320\267\320\264\320\265\320\273\320\270\321\202\321\214 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213 \321\200\320\260\320\267\320\275\320\276\320\263\320\276 \320\267\320\275\320\260\320\272\320\260", 0, QApplication::UnicodeUTF8));
        cmdFilter->setText(QString());
        lblCGH->setText(QApplication::translate("BalansRptForm", "\320\240\320\265\320\263\320\270\320\276\320\275:", 0, QApplication::UnicodeUTF8));
        cmbHoly->setItemText(0, QApplication::translate("BalansRptForm", "\320\233\321\216\320\261\320\276\320\271 \320\264\320\265\320\275\321\214", 0, QApplication::UnicodeUTF8));
        cmbHoly->setItemText(1, QApplication::translate("BalansRptForm", "\320\242\320\276\320\273\321\214\320\272\320\276 \321\200\320\260\320\261\320\276\321\207\320\270\320\265 \320\264\320\275\320\270", 0, QApplication::UnicodeUTF8));
        cmbHoly->setItemText(2, QApplication::translate("BalansRptForm", "\320\242\320\276\320\273\321\214\320\272\320\276 \320\262\321\213\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\275\320\270", 0, QApplication::UnicodeUTF8));

    } // retranslateUi

};

namespace Ui {
    class BalansRptForm: public Ui_BalansRptForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANSRPTFORM_H
