/********************************************************************************
** Form generated from reading UI file 'transformerexchange.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFORMEREXCHANGE_H
#define UI_TRANSFORMEREXCHANGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransformerExchange
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *mainlLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cmdAddImage;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TransformerExchange)
    {
        if (TransformerExchange->objectName().isEmpty())
            TransformerExchange->setObjectName(QString::fromUtf8("TransformerExchange"));
        TransformerExchange->resize(561, 193);
        verticalLayoutWidget = new QWidget(TransformerExchange);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 551, 181));
        mainlLayout = new QVBoxLayout(verticalLayoutWidget);
        mainlLayout->setObjectName(QString::fromUtf8("mainlLayout"));
        mainlLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 47, 13));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(60, 30, 91, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 30, 16, 16));
        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 30, 91, 20));

        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 30, 47, 13));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(170, 30, 91, 20));
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(60, 30, 91, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 30, 16, 16));

        verticalLayout_2->addWidget(groupBox_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        cmdAddImage = new QPushButton(verticalLayoutWidget);
        cmdAddImage->setObjectName(QString::fromUtf8("cmdAddImage"));

        horizontalLayout_2->addWidget(cmdAddImage);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        mainlLayout->addLayout(horizontalLayout);


        retranslateUi(TransformerExchange);
        QObject::connect(buttonBox, SIGNAL(accepted()), TransformerExchange, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TransformerExchange, SLOT(reject()));

        QMetaObject::connectSlotsByName(TransformerExchange);
    } // setupUi

    void retranslateUi(QDialog *TransformerExchange)
    {
        TransformerExchange->setWindowTitle(QApplication::translate("TransformerExchange", "\320\227\320\260\320\274\320\265\320\275\320\260 \321\202\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200\320\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TransformerExchange", "\320\242\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200 \321\202\320\276\320\272\320\260:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TransformerExchange", "\320\232\320\242\320\242 =", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TransformerExchange", "/", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TransformerExchange", "\320\242\321\200\320\260\320\275\321\201\321\204\320\276\321\200\320\274\320\260\321\202\320\276\321\200 \320\275\320\260\320\277\321\200\321\217\320\266\320\265\320\275\320\270\321\217:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TransformerExchange", "\320\232\320\242\320\235 =", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TransformerExchange", "/", 0, QApplication::UnicodeUTF8));
        cmdAddImage->setText(QApplication::translate("TransformerExchange", "\320\237\321\200\320\270\320\272\321\200\320\265\320\277\320\270\321\202\321\214 \320\260\320\272\321\202 \320\276 \320\267\320\260\320\274\320\265\320\275\320\265...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TransformerExchange: public Ui_TransformerExchange {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFORMEREXCHANGE_H
