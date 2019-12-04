/********************************************************************************
** Form generated from reading UI file 'BalansSelectElements.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANSSELECTELEMENTS_H
#define UI_BALANSSELECTELEMENTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BalansSelectElements
{
public:
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;
    QTreeWidget *twList;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *pbSelectPosPos;
    QPushButton *pbSelectNeg;
    QPushButton *pbSelect_2;
    QSpacerItem *verticalSpacer_2;
    QTreeWidget *twSelected;
    QHBoxLayout *hLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *BalansSelectElements)
    {
        if (BalansSelectElements->objectName().isEmpty())
            BalansSelectElements->setObjectName(QString::fromUtf8("BalansSelectElements"));
        BalansSelectElements->resize(694, 552);
        verticalLayoutWidget_2 = new QWidget(BalansSelectElements);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 0, 678, 541));
        mainLayout = new QVBoxLayout(verticalLayoutWidget_2);
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(5, 5, 5, 5);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        twList = new QTreeWidget(verticalLayoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        twList->setHeaderItem(__qtreewidgetitem);
        twList->setObjectName(QString::fromUtf8("twList"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(twList->sizePolicy().hasHeightForWidth());
        twList->setSizePolicy(sizePolicy);
        twList->setMinimumSize(QSize(300, 411));
        twList->setMaximumSize(QSize(16777215, 11111111));
        twList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        twList->setExpandsOnDoubleClick(false);
        twList->header()->setVisible(false);
        twList->header()->setCascadingSectionResizes(false);
        twList->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(twList);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, -1, 6, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pbSelectPosPos = new QPushButton(verticalLayoutWidget_2);
        pbSelectPosPos->setObjectName(QString::fromUtf8("pbSelectPosPos"));
        pbSelectPosPos->setMinimumSize(QSize(0, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/select_positive.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSelectPosPos->setIcon(icon);
        pbSelectPosPos->setIconSize(QSize(16, 16));

        verticalLayout->addWidget(pbSelectPosPos);

        pbSelectNeg = new QPushButton(verticalLayoutWidget_2);
        pbSelectNeg->setObjectName(QString::fromUtf8("pbSelectNeg"));
        pbSelectNeg->setMinimumSize(QSize(0, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/images/select_negative.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSelectNeg->setIcon(icon1);

        verticalLayout->addWidget(pbSelectNeg);

        pbSelect_2 = new QPushButton(verticalLayoutWidget_2);
        pbSelect_2->setObjectName(QString::fromUtf8("pbSelect_2"));
        pbSelect_2->setMinimumSize(QSize(0, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/images/deselect.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSelect_2->setIcon(icon2);

        verticalLayout->addWidget(pbSelect_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout);

        twSelected = new QTreeWidget(verticalLayoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QString::fromUtf8("1"));
        twSelected->setHeaderItem(__qtreewidgetitem1);
        twSelected->setObjectName(QString::fromUtf8("twSelected"));
        sizePolicy.setHeightForWidth(twSelected->sizePolicy().hasHeightForWidth());
        twSelected->setSizePolicy(sizePolicy);
        twSelected->setMinimumSize(QSize(300, 411));
        twSelected->setMaximumSize(QSize(16777215, 11111111));
        twSelected->setColumnCount(1);
        twSelected->header()->setVisible(false);
        twSelected->header()->setDefaultSectionSize(200);
        twSelected->header()->setMinimumSectionSize(20);
        twSelected->header()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(twSelected);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(2, 1);

        mainLayout->addLayout(horizontalLayout);

        hLayout = new QHBoxLayout();
        hLayout->setSpacing(0);
        hLayout->setObjectName(QString::fromUtf8("hLayout"));
        hLayout->setContentsMargins(6, 0, 6, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        hLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(verticalLayoutWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        hLayout->addWidget(pushButton);


        mainLayout->addLayout(hLayout);


        retranslateUi(BalansSelectElements);
        QObject::connect(pushButton, SIGNAL(clicked()), BalansSelectElements, SLOT(close()));
        QObject::connect(pbSelectNeg, SIGNAL(clicked()), BalansSelectElements, SLOT(itemSelectNegative()));
        QObject::connect(pbSelectPosPos, SIGNAL(clicked()), BalansSelectElements, SLOT(itemSelectPositive()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), BalansSelectElements, SLOT(saveChanges()));

        QMetaObject::connectSlotsByName(BalansSelectElements);
    } // setupUi

    void retranslateUi(QDialog *BalansSelectElements)
    {
        BalansSelectElements->setWindowTitle(QApplication::translate("BalansSelectElements", "Dialog", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pbSelectPosPos->setToolTip(QApplication::translate("BalansSelectElements", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\260\320\275\320\260\320\273\321\213 \321\201\320\276</span><span style=\" font-size:8pt; font-weight:600;\"> \320\267\320\275\320\260\320\272\320\276\320\274 &quot;\320\277\320\273\321\216\321\201&quot;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pbSelectPosPos->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbSelectNeg->setToolTip(QApplication::translate("BalansSelectElements", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\265 \320\272\320\260\320\275\320\260\320\273\321\213 \321\201\320\276<span style=\" font-weight:600;\"> \320\267\320\275\320\260\320\272\320\276\320\274 &quot;\320\274\320\270\320\275\321\203\321\201&quot;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pbSelectNeg->setText(QString());
        pbSelect_2->setText(QString());
        pushButton_2->setText(QApplication::translate("BalansSelectElements", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("BalansSelectElements", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BalansSelectElements: public Ui_BalansSelectElements {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANSSELECTELEMENTS_H
