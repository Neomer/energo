/********************************************************************************
** Form generated from reading UI file 'FeederDataForm.ui'
**
** Created: Thu 4. Oct 10:48:21 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEEDERDATAFORM_H
#define UI_FEEDERDATAFORM_H

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
#include <QtGui/QSpinBox>
#include <QtGui/QTableWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FeederDataForm
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
    QComboBox *cmbDisplayType;
    QLabel *label_5;
    QComboBox *cmbSource;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *twData;
    QGraphicsView *gvGraph;

    void setupUi(QWidget *FeederDataForm)
    {
        if (FeederDataForm->objectName().isEmpty())
            FeederDataForm->setObjectName(QString::fromUtf8("FeederDataForm"));
        FeederDataForm->resize(1066, 580);
        verticalLayoutWidget = new QWidget(FeederDataForm);
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
        icon.addFile(QString::fromUtf8(":/feederdata/images/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmdRefresh->setIcon(icon);
        cmdRefresh->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(cmdRefresh);

        cmdExcel = new QPushButton(verticalLayoutWidget);
        cmdExcel->setObjectName(QString::fromUtf8("cmdExcel"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/feederdata/images/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
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

        cmbDisplayType = new QComboBox(verticalLayoutWidget);
        cmbDisplayType->setObjectName(QString::fromUtf8("cmbDisplayType"));

        horizontalLayout_2->addWidget(cmbDisplayType);

        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        cmbSource = new QComboBox(verticalLayoutWidget);
        cmbSource->setObjectName(QString::fromUtf8("cmbSource"));

        horizontalLayout_2->addWidget(cmbSource);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        twData = new QTableWidget(verticalLayoutWidget);
        twData->setObjectName(QString::fromUtf8("twData"));
        twData->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

        verticalLayout->setStretch(2, 3);

        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(1, 50);

        mainLayout->addLayout(gridLayout);


        retranslateUi(FeederDataForm);

        cmbItvType->setCurrentIndex(1);
        cmbValueRound->setCurrentIndex(-1);
        cmbSource->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FeederDataForm);
    } // setupUi

    void retranslateUi(QWidget *FeederDataForm)
    {
        FeederDataForm->setWindowTitle(QApplication::translate("FeederDataForm", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twObjects->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("FeederDataForm", "\320\255\320\273\320\265\320\274\320\265\320\275\321\202\321\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FeederDataForm", "\320\235\320\260\321\207\320\260\320\273\320\276:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FeederDataForm", "\320\232\320\276\320\275\320\265\321\206:", 0, QApplication::UnicodeUTF8));
        cmbItvType->clear();
        cmbItvType->insertItems(0, QStringList()
         << QApplication::translate("FeederDataForm", "\320\227\320\260\320\264\320\260\321\202\321\214...", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FeederDataForm", "\320\241\321\203\321\202\320\272\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FeederDataForm", "\320\235\320\265\320\264\320\265\320\273\321\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FeederDataForm", "\320\234\320\265\321\201\321\217\321\206", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("FeederDataForm", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txtAccuracy->setToolTip(QApplication::translate("FeederDataForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\232\320\276\320\273-\320\262\320\276 \320\267\320\275\320\260\320\272\320\276\320\262 \320\277\320\276\321\201\320\273\320\265 \320\267\320\260\320\277\321\217\321\202\320\276\320\271.</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\320\265 -1, \320\264\320\273\321\217 \320\262\321\213\320\262\320\276\320\264\320\260 \320\264\320\260\320\275\320\275\321\213\321\205"
                        " &quot;\320\272\320\260\320\272 \320\265\321\201\321\202\321\214&quot;.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cmdRefresh->setToolTip(QApplication::translate("FeederDataForm", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdRefresh->setText(QString());
#ifndef QT_NO_TOOLTIP
        cmdExcel->setToolTip(QApplication::translate("FeederDataForm", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 MS Excel...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cmdExcel->setText(QString());
        label_4->setText(QApplication::translate("FeederDataForm", "\320\222\320\270\320\264 \320\276\321\202\321\207\320\265\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FeederDataForm", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272:", 0, QApplication::UnicodeUTF8));
        cmbSource->clear();
        cmbSource->insertItems(0, QStringList()
         << QApplication::translate("FeederDataForm", "\320\243\321\207\321\202\320\265\320\275\320\275\321\213\320\265 \320\277\321\200\320\276\321\204\320\270\320\273\320\270", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FeederDataForm", "\320\237\320\276\320\272\320\260\320\267\320\260\320\275\320\270\321\217 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class FeederDataForm: public Ui_FeederDataForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEEDERDATAFORM_H
