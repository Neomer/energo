/********************************************************************************
** Form generated from reading UI file 'ListPicker.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTPICKER_H
#define UI_LISTPICKER_H

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

class Ui_ListPicker
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *twList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdOK;
    QPushButton *pushButton_2;

    void setupUi(QDialog *ListPicker)
    {
        if (ListPicker->objectName().isEmpty())
            ListPicker->setObjectName(QString::fromUtf8("ListPicker"));
        ListPicker->resize(364, 408);
        horizontalLayoutWidget = new QWidget(ListPicker);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 351, 391));
        mainLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainLayout->setContentsMargins(6, 6, 6, 6);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        twList = new QTableWidget(horizontalLayoutWidget);
        twList->setObjectName(QString::fromUtf8("twList"));

        verticalLayout->addWidget(twList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 3, 0, 3);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdOK = new QPushButton(horizontalLayoutWidget);
        cmdOK->setObjectName(QString::fromUtf8("cmdOK"));
        cmdOK->setInputMethodHints(Qt::ImhNone);

        horizontalLayout->addWidget(cmdOK);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        mainLayout->addLayout(verticalLayout);

        QWidget::setTabOrder(twList, cmdOK);
        QWidget::setTabOrder(cmdOK, pushButton_2);

        retranslateUi(ListPicker);
        QObject::connect(pushButton_2, SIGNAL(clicked()), ListPicker, SLOT(close()));
        QObject::connect(cmdOK, SIGNAL(clicked()), ListPicker, SLOT(okPressed()));

        QMetaObject::connectSlotsByName(ListPicker);
    } // setupUi

    void retranslateUi(QDialog *ListPicker)
    {
        ListPicker->setWindowTitle(QApplication::translate("ListPicker", "Dialog", 0, QApplication::UnicodeUTF8));
        cmdOK->setText(QApplication::translate("ListPicker", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("ListPicker", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ListPicker: public Ui_ListPicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTPICKER_H
