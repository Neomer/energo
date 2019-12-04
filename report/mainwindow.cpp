#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QFormLayout>
#include <QGridLayout>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setAttribute(Qt::WA_QuitOnClose, true);
	mdi_area = new QMdiArea;
    mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdi_area);
	connect(mdi_area, SIGNAL(subWindowActivated(QMdiSubWindow*)),
	        this, SLOT(mdiSelected(QMdiSubWindow*)));
	
	connect(ui->actPrint, SIGNAL(triggered()), this, SLOT(print()));
	connect(ui->actPrintPreview, SIGNAL(triggered()), this, SLOT(printPreview()));
	
	this->mdi = 0;
	this->conn = 0;
	ui->mainToolBar->addAction(QIcon(":/toolbar/images/print.png"), tr("Печать"), this, SLOT(print()));
	ui->actPrint->setIcon(QIcon(":/icons/images/print16.png"));
	ui->actPrintPreview->setIcon(QIcon(":/icons/images/print_preview.png"));
	
	connect(ui->mnuCheckData, SIGNAL(triggered()), this, SLOT(onReportSelect()));
	QDir dir;
	QStringList filter;
	filter << "*.dll";
	dir.setNameFilters(filter);
	dir.setPath(dir.absolutePath().append("/reports/"));
	filter = dir.entryList(QDir::Files);
	QString err_rep = "";
	qDebug("MainWindow::MainWindow() - Load report plugins from: %s", 
	       dir.path().toAscii().constData());
	for (int i = 0; i < filter.count(); i++)
	{
		AbstractReportPlugin * report;
		QPluginLoader pl(dir.path().append("/").append(filter.at(i)));
		if (pl.load())
		{
			QAction * act = new QAction(ui->mnuReports);
			report = qobject_cast<AbstractReportPlugin *>(pl.instance());
			act->setText(report->getName());
			pl.unload();
			connect(act, SIGNAL(triggered()), this, SLOT(onReportSelect()));
			ui->mnuReports->addAction(act);
			act->setData(QVariant::fromValue(filter.at(i)));
		}
		else
			err_rep = err_rep.append(filter.at(i)).append("\n");
	}
	if (err_rep != "")
		QMessageBox::critical(this, tr("Ошибка"), tr("Не все отчеты были загружены!\n").append(err_rep));
}

MainWindow::~MainWindow()
{
	if (ui) 
	{
		delete ui;
	}
}

/******************************************************************
  
			SLOTS

*******************************************************************/

void MainWindow::mdiSelected(QMdiSubWindow * mdi)
{
	if (mdi)
	{
		this->mdi = mdi;
		//this->setWindowTitle(tr("Energo - Отчеты <-> ").append(mdi->windowTitle()));
	}
}

void MainWindow::print()
{
	if (!mdi)
	{
		QMessageBox::warning(this, tr("Печать - Ошибка"), tr("Необходимо выбрать отчет!"));
		return;
	}
	ReportEngine * re = new ReportEngine();
	_plugins[mdi_area->currentSubWindow()]->getPrintableForm(re);
	//re->showPrintPreviewDialog(this);
	re->showPrintDialog(this);
}

void MainWindow::printPreview()
{
	if (!mdi)
	{
		QMessageBox::warning(this, tr("Печать - Ошибка"), tr("Необходимо выбрать отчет!"));
		return;
	}
	ReportEngine * re = new ReportEngine();
	_plugins[mdi_area->currentSubWindow()]->getPrintableForm(re);
	re->showPrintPreviewDialog(this);
}

void MainWindow::login_fail()
{
	if (!this->close())
		QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно закрыть окно"));
}


void MainWindow::db_connected(PgreSqlDrv *connection)
{
	this->conn = connection;
}

void MainWindow::login_form_closed()
{
	if (!this->conn) login_fail();
}

void MainWindow::onReportSelect()
{
	QAction * action = qobject_cast<QAction *>(QObject::sender());
	QMdiSubWindow * mdi = new QMdiSubWindow();
	QMdiSubWindow * window = this->mdi_area->addSubWindow(mdi, Qt::SubWindow);
	window->setWindowTitle(action->text());
	delete window->layout();
	QGridLayout * layout = new QGridLayout(window);
	layout->setSpacing(5);
	window->resize(800, 600);
	window->setLayout(layout);
	window->setWindowState(Qt::WindowMaximized);
	window->setWindowIcon(QIcon(":/icons/conf.ico"));
	window->show();
	AbstractReportPlugin * plugin;
	QDir dir;
	QPluginLoader * pl = new QPluginLoader(dir.currentPath().append("/reports/").append(action->data().toString()));
	if (pl->load())
	{
		plugin = qobject_cast<AbstractReportPlugin *>(pl->instance());
		plugin->load(this->conn, window);
		_plugins[window] = plugin;
	}
	else
		QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно загрузить отчет!"));
}
