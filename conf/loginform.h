#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QMutex>
#include <QSettings>

//#include "../includes/dbconf.h"
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
    void setMutex(QMutex *mtx);

public slots:
    void connect2db();

signals:
    void onAuthFail();
	void onDBConnected(PgreSqlDrv * connection);
	void onClose();

private:
	void closeEvent(QCloseEvent * event);
    PGconn *c;
	PgreSqlDrv * m_conn;
    Ui::LoginForm *ui;
    QMutex *mtx;
	QSettings * settings;
};

#endif // LOGINFORM_H
