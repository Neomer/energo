#include "debugwindow.h"
#include "ui_debugwindow.h"

DebugWindow::DebugWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebugWindow)
{
    ui->setupUi(this);
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);

	log_file = new QFile();
	log_file->setFileName(QDir::currentPath().append("/logs/log_conf_").append(QDateTime::currentDateTime().toString("yyyy_MM_dd")).append(".log"));
	log_file->open(QIODevice::Append);
}

DebugWindow::~DebugWindow()
{
    delete ui;
	log_file->close();
}


/******************************************************************
  
			METHODS

*******************************************************************/

void DebugWindow::addRow(QString text)
{
	ui->txtDebug->appendPlainText(text);
	QString s = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ").append(text);
	if (s.at(s.length() - 1) != '\n') s.append('\n');
	log_file->write(s.toAscii().constData(), s.length());
}
