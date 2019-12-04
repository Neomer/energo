#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "defines.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowTitle(MAIN_TITLE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
	ui->lblText->setText(tr("Установление соединения..."));
	_conn = new TcpConnection();
	connect(_conn, SIGNAL(onConnectionFail()), this, SLOT(connectionFailed()));
	connect(_conn, SIGNAL(onConnectionSuccess()), this, SLOT(connectionSuccess()));
	connect(_conn, SIGNAL(onNewFile(QString)), this, SLOT(newFile(QString)));
	connect(_conn, SIGNAL(onProgress(int)), this, SLOT(progressChanged(int)));
	connect(_conn, SIGNAL(onFinish()), this, SLOT(updateFinish()));
}

void MainWindow::connectionFailed()
{
	ui->lblText->setText(tr("Сервер обновлений недоступен!"));
}

void MainWindow::connectionSuccess()
{
	ui->lblText->setText(tr("Успешное соединение с сервером обновлений"));
}

void MainWindow::newFile(QString name)
{
	ui->lblText->setText(tr("Файл: %1").arg(name.toAscii().constData()));
}

void MainWindow::progressChanged(int value)
{
	ui->pb->setValue(value);
}

void MainWindow::updateFinish()
{
	ui->lblText->setText(tr("Обновление завершено!"));
}
