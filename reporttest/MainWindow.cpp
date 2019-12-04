#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowState(Qt::WindowMaximized);
	QDeclarativeView * qdv = new QDeclarativeView(this);
	QDeclarativeContext * context = qdv->rootContext();
	context->setContextProperty("window", this);
	qdv->setSource(QUrl::fromLocalFile("D:/project/Qt/energo/reporttest/report.qml"));
	setCentralWidget(qdv);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getData()
{
	QString ret = "{\"rows\": [\"value 1\" , \"value 2\"]}";
	return ret;
}
