/********************************************************************************
** Form generated from reading UI file 'dataviewdlg.ui'
**
** Created: Wed 30. Nov 10:21:03 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAVIEWDLG_H
#define UI_DATAVIEWDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataViewDlg
{
public:
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QLineEdit *txtDate;
    QPushButton *btnCalendar;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cmdArecv;
    QPushButton *cmdAsend;
    QPushButton *cmdQrecv;
    QPushButton *cmdQsend;
    QSpacerItem *horizontalSpacer_3;
    QTableWidget *tvData;

    void setupUi(QDialog *DataViewDlg)
    {
        if (DataViewDlg->objectName().isEmpty())
            DataViewDlg->setObjectName(QString::fromUtf8("DataViewDlg"));
        DataViewDlg->setWindowModality(Qt::WindowModal);
        DataViewDlg->resize(581, 731);
        horizontalLayoutWidget_3 = new QWidget(DataViewDlg);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 0, 581, 731));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget_3);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(horizontalLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setTextFormat(Qt::PlainText);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        txtDate = new QLineEdit(horizontalLayoutWidget_3);
        txtDate->setObjectName(QString::fromUtf8("txtDate"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtDate->sizePolicy().hasHeightForWidth());
        txtDate->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        txtDate->setFont(font);
        txtDate->setFrame(true);
        txtDate->setEchoMode(QLineEdit::Normal);
        txtDate->setCursorPosition(10);
        txtDate->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(txtDate);

        btnCalendar = new QPushButton(horizontalLayoutWidget_3);
        btnCalendar->setObjectName(QString::fromUtf8("btnCalendar"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(5);
        sizePolicy2.setHeightForWidth(btnCalendar->sizePolicy().hasHeightForWidth());
        btnCalendar->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/viewdlg/images/calendar.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCalendar->setIcon(icon);
        btnCalendar->setIconSize(QSize(22, 22));
        btnCalendar->setAutoDefault(false);

        horizontalLayout->addWidget(btnCalendar);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cmdArecv = new QPushButton(horizontalLayoutWidget_3);
        cmdArecv->setObjectName(QString::fromUtf8("cmdArecv"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cmdArecv->sizePolicy().hasHeightForWidth());
        cmdArecv->setSizePolicy(sizePolicy3);
        cmdArecv->setMaximumSize(QSize(40, 16777215));
        cmdArecv->setIconSize(QSize(0, 0));
        cmdArecv->setCheckable(true);
        cmdArecv->setDefault(true);

        horizontalLayout_2->addWidget(cmdArecv);

        cmdAsend = new QPushButton(horizontalLayoutWidget_3);
        cmdAsend->setObjectName(QString::fromUtf8("cmdAsend"));
        cmdAsend->setMaximumSize(QSize(40, 16777215));
        cmdAsend->setCheckable(true);

        horizontalLayout_2->addWidget(cmdAsend);

        cmdQrecv = new QPushButton(horizontalLayoutWidget_3);
        cmdQrecv->setObjectName(QString::fromUtf8("cmdQrecv"));
        cmdQrecv->setMaximumSize(QSize(40, 16777215));
        cmdQrecv->setCheckable(true);

        horizontalLayout_2->addWidget(cmdQrecv);

        cmdQsend = new QPushButton(horizontalLayoutWidget_3);
        cmdQsend->setObjectName(QString::fromUtf8("cmdQsend"));
        cmdQsend->setMaximumSize(QSize(40, 16777215));
        cmdQsend->setCheckable(true);

        horizontalLayout_2->addWidget(cmdQsend);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tvData = new QTableWidget(horizontalLayoutWidget_3);
        tvData->setObjectName(QString::fromUtf8("tvData"));

        gridLayout->addWidget(tvData, 2, 0, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(DataViewDlg);

        QMetaObject::connectSlotsByName(DataViewDlg);
    } // setupUi

    void retranslateUi(QDialog *DataViewDlg)
    {
        DataViewDlg->setWindowTitle(QApplication::translate("DataViewDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DataViewDlg", "\320\224\320\260\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        txtDate->setText(QApplication::translate("DataViewDlg", "2011-10-01", 0, QApplication::UnicodeUTF8));
        btnCalendar->setText(QString());
        cmdArecv->setText(QApplication::translate("DataViewDlg", "A+", 0, QApplication::UnicodeUTF8));
        cmdAsend->setText(QApplication::translate("DataViewDlg", "A-", 0, QApplication::UnicodeUTF8));
        cmdQrecv->setText(QApplication::translate("DataViewDlg", "\320\240+", 0, QApplication::UnicodeUTF8));
        cmdQsend->setText(QApplication::translate("DataViewDlg", "\320\240-", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DataViewDlg: public Ui_DataViewDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAVIEWDLG_H
