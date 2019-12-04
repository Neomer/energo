/********************************************************************************
** Form generated from reading UI file 'loginform.ui'
**
** Created: Fri 22. Jun 13:05:24 2012
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINFORM_H
#define UI_LOGINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginForm
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *txtLogin;
    QLineEdit *txtPassword;
    QLineEdit *txtDB;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    void setupUi(QDialog *LoginForm)
    {
        if (LoginForm->objectName().isEmpty())
            LoginForm->setObjectName(QString::fromUtf8("LoginForm"));
        LoginForm->resize(400, 167);
        LoginForm->setMinimumSize(QSize(400, 167));
        LoginForm->setMaximumSize(QSize(400, 167));
        label = new QLabel(LoginForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 41, 16));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(LoginForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 50, 51, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(LoginForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 80, 71, 16));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtLogin = new QLineEdit(LoginForm);
        txtLogin->setObjectName(QString::fromUtf8("txtLogin"));
        txtLogin->setGeometry(QRect(100, 20, 241, 20));
        txtPassword = new QLineEdit(LoginForm);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(100, 50, 241, 20));
        txtPassword->setEchoMode(QLineEdit::Password);
        txtDB = new QLineEdit(LoginForm);
        txtDB->setObjectName(QString::fromUtf8("txtDB"));
        txtDB->setGeometry(QRect(100, 80, 241, 20));
        btnOK = new QPushButton(LoginForm);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 120, 141, 31));
        btnCancel = new QPushButton(LoginForm);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(220, 120, 141, 31));

        retranslateUi(LoginForm);

        QMetaObject::connectSlotsByName(LoginForm);
    } // setupUi

    void retranslateUi(QDialog *LoginForm)
    {
        LoginForm->setWindowTitle(QApplication::translate("LoginForm", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LoginForm", "\320\233\320\276\320\263\320\270\320\275:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LoginForm", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("LoginForm", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205:", 0, QApplication::UnicodeUTF8));
        txtLogin->setText(QApplication::translate("LoginForm", "postgres", 0, QApplication::UnicodeUTF8));
        txtPassword->setInputMask(QString());
        txtPassword->setText(QApplication::translate("LoginForm", "1234", 0, QApplication::UnicodeUTF8));
        txtPassword->setPlaceholderText(QString());
        txtDB->setText(QApplication::translate("LoginForm", "energo", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("LoginForm", "\320\236\320\232", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("LoginForm", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginForm: public Ui_LoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINFORM_H
