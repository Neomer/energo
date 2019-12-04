/********************************************************************************
** Form generated from reading UI file 'SearchDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDIALOG_H
#define UI_SEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
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

class Ui_SearchDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainlLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *txtCounter;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cmdSearch;
    QPushButton *cmdCancel;
    QLabel *label_2;
    QLineEdit *txtFeeder;
    QLabel *label_3;
    QLineEdit *txtObject;
    QTableWidget *twResult;

    void setupUi(QWidget *SearchDialog)
    {
        if (SearchDialog->objectName().isEmpty())
            SearchDialog->setObjectName(QString::fromUtf8("SearchDialog"));
        SearchDialog->setWindowModality(Qt::WindowModal);
        SearchDialog->resize(468, 449);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SearchDialog->sizePolicy().hasHeightForWidth());
        SearchDialog->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(SearchDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 451, 431));
        mainlLayout = new QVBoxLayout(verticalLayoutWidget);
        mainlLayout->setContentsMargins(6, 6, 6, 6);
        mainlLayout->setObjectName(QString::fromUtf8("mainlLayout"));
        mainlLayout->setSizeConstraint(QLayout::SetMinimumSize);
        mainlLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        txtCounter = new QLineEdit(verticalLayoutWidget);
        txtCounter->setObjectName(QString::fromUtf8("txtCounter"));

        gridLayout->addWidget(txtCounter, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cmdSearch = new QPushButton(verticalLayoutWidget);
        cmdSearch->setObjectName(QString::fromUtf8("cmdSearch"));

        horizontalLayout->addWidget(cmdSearch);

        cmdCancel = new QPushButton(verticalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout->addWidget(cmdCancel);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        txtFeeder = new QLineEdit(verticalLayoutWidget);
        txtFeeder->setObjectName(QString::fromUtf8("txtFeeder"));

        gridLayout->addWidget(txtFeeder, 2, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        txtObject = new QLineEdit(verticalLayoutWidget);
        txtObject->setObjectName(QString::fromUtf8("txtObject"));

        gridLayout->addWidget(txtObject, 3, 1, 1, 1);


        mainlLayout->addLayout(gridLayout);

        twResult = new QTableWidget(verticalLayoutWidget);
        twResult->setObjectName(QString::fromUtf8("twResult"));

        mainlLayout->addWidget(twResult);


        retranslateUi(SearchDialog);
        QObject::connect(cmdCancel, SIGNAL(clicked()), SearchDialog, SLOT(close()));
        QObject::connect(cmdSearch, SIGNAL(clicked()), SearchDialog, SLOT(search()));

        QMetaObject::connectSlotsByName(SearchDialog);
    } // setupUi

    void retranslateUi(QWidget *SearchDialog)
    {
        SearchDialog->setWindowTitle(QApplication::translate("SearchDialog", "\320\235\320\260\320\271\321\202\320\270", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchDialog", "\320\235\320\276\320\274\320\265\321\200 \321\201\321\207\320\265\321\202\321\207\320\270\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        txtCounter->setText(QApplication::translate("SearchDialog", "%", 0, QApplication::UnicodeUTF8));
        cmdSearch->setText(QApplication::translate("SearchDialog", "\320\235\320\260\320\271\321\202\320\270", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("SearchDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("SearchDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265 \321\204\320\270\320\264\320\265\321\200\320\260:", 0, QApplication::UnicodeUTF8));
        txtFeeder->setText(QApplication::translate("SearchDialog", "%", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SearchDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\320\260:", 0, QApplication::UnicodeUTF8));
        txtObject->setText(QApplication::translate("SearchDialog", "%", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchDialog: public Ui_SearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDIALOG_H
