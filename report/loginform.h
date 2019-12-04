#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QMutex>
#include <QSettings>
#include "mainwindow.h"

namespace Ui {
    class LoginForm;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

public slots:
    void connect2db();
	void closeEvent(QCloseEvent * event);

signals:
    void onAuthFail();
	void onDBConnected(PgreSqlDrv * connection);
	void onClose();

private:
	PgreSqlDrv * c;
    Ui::LoginForm *ui;
	QSettings * settings;
};

#endif // LOGINFORM_H
