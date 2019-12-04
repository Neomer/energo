#include "PlanningLoginForm.h"
#include <QApplication>
#include <QCloseEvent>
#include "ui_PlanningLoginForm.h"
#include "../includes/dbconf.h"
#include <QMessageBox>

PlanningLoginForm::PlanningLoginForm(QSettings * settings, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PlanningLoginForm)
{
	ui->setupUi(this);
	
	setWindowTitle(tr("Авторизация"));
	
	connect(ui->btnCancel, SIGNAL(clicked()),
			qApp, SLOT(quit()));
	
	_settings = settings;
	
	initdbhost();
	
	ui->txtDB->setText(_settings->value("db.name", DB_NAME).toString());
	ui->txtLogin->setText(_settings->value("planning.user", DB_USER).toString());
	
	connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(connect2db()));
	
}

PlanningLoginForm::~PlanningLoginForm()
{
	delete ui;
}

void PlanningLoginForm::connect2db()
{
	PgreSqlDrv * conn = new PgreSqlDrv();
	if (!conn->connect(_settings->value("db.host", QString("127.0.0.1")).toString(),
				  _settings->value("db.user", QString("postgres")).toString(),
				  _settings->value("db.password", QString("1234")).toString(),
				  ui->txtDB->text(),
				  true))
	{
		QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось подключиться к БД!"));
		close();
	}
	
	PgreSqlResult * r = conn->exec(QString("select id from users where login='%1' and password=md5('%2');").arg(
									   ui->txtLogin->text(),
									   ui->txtPassword->text()));
	if (!r->isValid())
		QMessageBox::critical(this, tr("Ошибка"), tr("Ошибка запроса к БД!\n").append(
								  conn->getError()));
	else
	{
		if (r->hasRows())
			emit connectToDatabase(conn, r->getValue(0).toInt());
		else
		{
			QMessageBox::critical(this, tr("Ошибка"), tr("Неверный логин или пароль!"));
			return;
		}
	}
	close();
}

void PlanningLoginForm::closeEvent(QCloseEvent *e)
{
	_settings->setValue("db.name", ui->txtDB->text());
	_settings->setValue("planning.user", ui->txtLogin->text());
	emit onClose();
	e->accept();
}
