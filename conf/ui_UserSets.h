/********************************************************************************
** Form generated from reading UI file 'UserSets.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSETS_H
#define UI_USERSETS_H

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
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserSets
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *txtPassword;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cmdSave;
    QPushButton *cmdCancel;
    QLabel *label_4;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtName;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QTreeWidget *twAccess;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *txtLogin;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *UserSets)
    {
        if (UserSets->objectName().isEmpty())
            UserSets->setObjectName(QString::fromUtf8("UserSets"));
        UserSets->resize(660, 518);
        verticalLayoutWidget = new QWidget(UserSets);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 641, 501));
        mainLayout = new QVBoxLayout(verticalLayoutWidget);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setContentsMargins(6, 6, 6, 6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        txtPassword = new QLineEdit(verticalLayoutWidget);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtPassword->sizePolicy().hasHeightForWidth());
        txtPassword->setSizePolicy(sizePolicy);
        txtPassword->setMinimumSize(QSize(250, 0));
        txtPassword->setMaximumSize(QSize(50, 16777215));
        txtPassword->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(txtPassword);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 5, -1, -1);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cmdSave = new QPushButton(verticalLayoutWidget);
        cmdSave->setObjectName(QString::fromUtf8("cmdSave"));

        horizontalLayout_4->addWidget(cmdSave);

        cmdCancel = new QPushButton(verticalLayoutWidget);
        cmdCancel->setObjectName(QString::fromUtf8("cmdCancel"));

        horizontalLayout_4->addWidget(cmdCancel);


        gridLayout->addLayout(horizontalLayout_4, 5, 1, 1, 1);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtName = new QLineEdit(verticalLayoutWidget);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setMinimumSize(QSize(250, 0));
        txtName->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(txtName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, -1, -1, -1);
        twAccess = new QTreeWidget(verticalLayoutWidget);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/images/tag-green.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(twAccess);
        __qtreewidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        __qtreewidgetitem->setCheckState(0, Qt::Checked);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(twAccess);
        __qtreewidgetitem1->setCheckState(0, Qt::Checked);
        __qtreewidgetitem1->setIcon(0, icon);
        twAccess->setObjectName(QString::fromUtf8("twAccess"));
        twAccess->header()->setVisible(false);

        horizontalLayout_5->addWidget(twAccess);


        gridLayout->addLayout(horizontalLayout_5, 4, 1, 1, 1);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        txtLogin = new QLineEdit(verticalLayoutWidget);
        txtLogin->setObjectName(QString::fromUtf8("txtLogin"));
        txtLogin->setMinimumSize(QSize(250, 0));
        txtLogin->setMaximumSize(QSize(250, 16777215));

        horizontalLayout_3->addWidget(txtLogin);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 1, 1, 1, 1);


        mainLayout->addLayout(gridLayout);


        retranslateUi(UserSets);

        QMetaObject::connectSlotsByName(UserSets);
    } // setupUi

    void retranslateUi(QWidget *UserSets)
    {
        UserSets->setWindowTitle(QApplication::translate("UserSets", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UserSets", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        cmdSave->setText(QApplication::translate("UserSets", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        cmdCancel->setText(QApplication::translate("UserSets", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UserSets", "\320\237\321\200\320\260\320\262\320\260 \320\264\320\276\321\201\321\202\321\203\320\277\320\260:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UserSets", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = twAccess->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("UserSets", "\320\237\321\200\320\260\320\262\320\276 \320\264\320\276\321\201\321\202\321\203\320\277\320\260", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = twAccess->isSortingEnabled();
        twAccess->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = twAccess->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("UserSets", "\320\247\321\202\320\265\320\275\320\270\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = twAccess->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("UserSets", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\215\320\273\320\265\320\274\320\265\320\275\321\202\320\276\320\262", 0, QApplication::UnicodeUTF8));
        twAccess->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("UserSets", "\320\233\320\276\320\263\320\270\320\275:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserSets: public Ui_UserSets {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSETS_H
