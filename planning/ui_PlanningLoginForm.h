/********************************************************************************
** Form generated from reading UI file 'PlanningLoginForm.ui'
**
** Created: Tue 22. May 15:32:07 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANNINGLOGINFORM_H
#define UI_PLANNINGLOGINFORM_H

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

class Ui_PlanningLoginForm
{
public:
    QLineEdit *txtDB;
    QPushButton *btnCancel;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *txtLogin;
    QLabel *label_2;
    QPushButton *btnOK;
    QLineEdit *txtPassword;

    void setupUi(QDialog *PlanningLoginForm)
    {
        if (PlanningLoginForm->objectName().isEmpty())
            PlanningLoginForm->setObjectName(QString::fromUtf8("PlanningLoginForm"));
        PlanningLoginForm->resize(394, 153);
        txtDB = new QLineEdit(PlanningLoginForm);
        txtDB->setObjectName(QString::fromUtf8("txtDB"));
        txtDB->setGeometry(QRect(100, 70, 241, 20));
        btnCancel = new QPushButton(PlanningLoginForm);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(220, 110, 141, 31));
        label_3 = new QLabel(PlanningLoginForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 71, 16));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(PlanningLoginForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 10, 41, 16));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtLogin = new QLineEdit(PlanningLoginForm);
        txtLogin->setObjectName(QString::fromUtf8("txtLogin"));
        txtLogin->setGeometry(QRect(100, 10, 241, 20));
        label_2 = new QLabel(PlanningLoginForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 40, 51, 16));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnOK = new QPushButton(PlanningLoginForm);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 110, 141, 31));
        txtPassword = new QLineEdit(PlanningLoginForm);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(100, 40, 241, 20));
        txtPassword->setEchoMode(QLineEdit::Password);
        QWidget::setTabOrder(txtPassword, txtDB);
        QWidget::setTabOrder(txtDB, btnOK);
        QWidget::setTabOrder(btnOK, btnCancel);
        QWidget::setTabOrder(btnCancel, txtLogin);

        retranslateUi(PlanningLoginForm);

        QMetaObject::connectSlotsByName(PlanningLoginForm);
    } // setupUi

    void retranslateUi(QDialog *PlanningLoginForm)
    {
        PlanningLoginForm->setWindowTitle(QApplication::translate("PlanningLoginForm", "Dialog", 0, QApplication::UnicodeUTF8));
        txtDB->setText(QApplication::translate("PlanningLoginForm", "energo", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("PlanningLoginForm", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PlanningLoginForm", "\320\221\320\260\320\267\320\260 \320\264\320\260\320\275\320\275\321\213\321\205:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlanningLoginForm", "\320\233\320\276\320\263\320\270\320\275:", 0, QApplication::UnicodeUTF8));
        txtLogin->setText(QApplication::translate("PlanningLoginForm", "postgres", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PlanningLoginForm", "\320\237\320\260\321\200\320\276\320\273\321\214:", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("PlanningLoginForm", "\320\236\320\232", 0, QApplication::UnicodeUTF8));
        txtPassword->setInputMask(QString());
        txtPassword->setText(QString());
        txtPassword->setPlaceholderText(QString());
    } // retranslateUi

};

namespace Ui {
    class PlanningLoginForm: public Ui_PlanningLoginForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANNINGLOGINFORM_H
