#include "MainWindow.h"
#include "ui_XmlImportMW.h"

#include "EMailMessage.h"
#include "XML80020.h"
#include "FileChecker.h"
#include <QFile>
#include "../pgredrv/PgreSqlDrv.h"
#include <QDateTime>
#include <QScrollBar>
#include <QMessageBox>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	
	if (QSystemTrayIcon::isSystemTrayAvailable())
	{
		QIcon trayico = QIcon(":/xmlimport/images/tray.png");		
		
		_tray = new QSystemTrayIcon(this);
		_tray->setIcon(trayico);
		_tray->setToolTip(this->windowTitle());
		QMenu * mnu = new QMenu(this);
		mnu->addAction(tr("Test"));
		//_tray->setContextMenu(mnu);
	}
	else
	{
		_tray = 0;
	}
	
	connect(_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
	if (_tray) _tray->show();
	//_tray->showMessage(tr("Hello"), tr("WELCOME TO HELL!"));
	
	if (ui->centralWidget->layout()) delete ui->centralWidget->layout();
	ui->centralWidget->setLayout(ui->mainLayout);

	FileChecker * fchk = new FileChecker(QDir::currentPath().append("/m80020/"), this);
	connect(fchk, SIGNAL(generateMessage(QString)), this, SLOT(appendLog(QString)));
	fchk->startLoop();
	
	/*
	QFile file("msg.txt");
	if (!file.open(QIODevice::ReadOnly))
		appendLog(tr("Нет файла с письмом!"));
	else
	{
		EMailMessage * msg = new EMailMessage(file.readAll());
		file.close();
		
		file.setFileName("testattch.txt");
		file.open(QIODevice::WriteOnly);
		EMailBody * body = msg->getBody(BT_ATTACHMENT);
		file.write(body->getContent());
		file.close();
		appendLog(body->getFileName());
	}
	*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::appendLog(QString text)
{
	ui->txtLog->setPlainText(ui->txtLog->toPlainText().append(QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] - ")).append(text));
	ui->txtLog->verticalScrollBar()->setValue(ui->txtLog->verticalScrollBar()->maximum());
}

void MainWindow::visibilityChange()
{
	if (isVisible())
		hide();
	else
	{
		show();
		setWindowState(Qt::WindowNoState);
	}
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		case QSystemTrayIcon::Trigger:
			visibilityChange();
			break;
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (_tray->isVisible())
		_tray->hide();
}

void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange)
	{
		if (isMinimized())
		{
			QTimer::singleShot(0, this, SLOT(hide()));
			event->ignore();
			return;
		}
	}
	QMainWindow::changeEvent(event);
}

