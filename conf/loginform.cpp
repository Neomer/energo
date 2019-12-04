#include "loginform.h"
#include "ui_loginform.h"
#include <QCloseEvent>

LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

	//this->setAttribute(Qt::WA_DeleteOnClose, true);
	settings = new QSettings("energo.conf", QSettings::IniFormat, this);
	
	ui->txtDB->setText(settings->value("db.name", QString()).toString());
	ui->txtLogin->setText(settings->value("db.user", QString()).toString());
	ui->txtPassword->setText(settings->value("db.password", QString()).toString());
	
    connect(this->ui->btnOK, SIGNAL(clicked()), this, SLOT(connect2db()));
}

LoginForm::~LoginForm()
{
    if (ui) delete ui;
}

void LoginForm::setMutex(QMutex *mtx)
{
    this->mtx = mtx;
}

void LoginForm::closeEvent(QCloseEvent * event)
{
	event->accept();
	emit onClose();
}

void LoginForm::connect2db()
{
	
	QString DB_HOST = settings->value("db.host", QString("127.0.0.1")).toString();
	
    // Формируем строку соединения с БД
	QString cs = "host=%1 user=%2 password=%3 dbname=%4";
	cs = cs.arg(DB_HOST).arg(ui->txtLogin->text()).arg(ui->txtPassword->text()).arg(ui->txtDB->text());
    qWarning("LF:: connect2db() - %s", cs.toAscii().constData());
	
	PgreSqlDrv * m_conn = new PgreSqlDrv();
	// Соединение с БД
	if (!m_conn->connect(DB_HOST, ui->txtLogin->text(), ui->txtPassword->text(), ui->txtDB->text()))
	{
        qWarning("LF:: connect2db() - DB connection failed!");
        QMessageBox::critical(this, QObject::tr("Ошибка"), QObject::tr("Невозможно подключиться к БД"));
		emit onAuthFail();
		this->close();
    }
	
	emit onDBConnected(m_conn);
	this->close();
}
