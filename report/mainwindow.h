#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QPrinterInfo>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPrintDialog>
#include <QList>
#include <QAction>
#include <QMap>
#include <QPluginLoader>
#include "../includes/AbstractReportPlugin.h"

#include "../pgredrv/PgreSqlDrv.h"
#include "MdiWindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void login_fail();
	void db_connected(PgreSqlDrv * connection);	
	void print();
	void printPreview();
	void mdiSelected(QMdiSubWindow * mdi);
	void login_form_closed();
	//void closeEvent(QCloseEvent *);
	//void printer_selected();
	void onReportSelect();
	
private:
    Ui::MainWindow *ui;
	QMdiArea * mdi_area;
	PgreSqlDrv * conn;
	QMdiSubWindow * mdi;
	QList<QAction *> acts;
	QMap<QMdiSubWindow *, AbstractReportPlugin *> _plugins;
};

#endif // MAINWINDOW_H
