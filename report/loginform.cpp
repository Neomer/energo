#include "loginform.h"
#include "ui_loginform.h"
#include <QCloseEvent>
#include <QSettings>

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
	this->c = 0;
	settings = new QSettings("energo.conf", QSettings::IniFormat, this);
	ui->txtLogin->setText(settings->value("db.user").toString());
	ui->txtDB->setText(settings->value("db.name").toString());
	ui->txtPassword->setText(settings->value("db.password").toString());
	
    connect(this->ui->btnOK, SIGNAL(clicked()), this, SLOT(connect2db()));
	connect(this->ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
}

LoginForm::~LoginForm()
{
    if (ui) 
	{
		delete ui;
	}
}

void LoginForm::closeEvent(QCloseEvent * event)
{
	if (!this->c) 
		event->ignore();
	else
		event->accept();
	emit onClose();
}

void LoginForm::connect2db()
{
	
	QString DB_HOST = settings->value("db.host", QString("127.0.0.1")).toString();
	
	c = new PgreSqlDrv();
    // Соединение с БД
    if (!c->connect(DB_HOST, ui->txtLogin->text(), ui->txtPassword->text(), ui->txtDB->text()))
    {
        qWarning("LF:: connect2db() - DB connection failed!");
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Невозможно подключиться к БД"));
		emit onAuthFail();
		this->close();
    }
	emit onDBConnected(c);
	this->close();
}
