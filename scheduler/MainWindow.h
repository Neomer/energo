#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTreeWidgetItem>

#include "../pgredrv/PgreSqlDrv.h"
#include "ScheduleList.h"
#include "Timer.h"
#include "InstanceController.h"
#include <QSettings>
#include "global.h"

namespace Ui {
	class MainWindow;
}

struct TreeElementDesc
{
	int ID;
	TreeElement type;
	Schedule * schedule;
};

class MainWindow : public QMainWindow
{
		Q_OBJECT
		
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		
	private slots:
		void taskStarted();
		void taskFinished();
		void taskSelected(QTreeWidgetItem * item, int column);
		void taskStart();
		void taskTerminate();
		void taskMessageReceived();
		void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
		void updateTree(QTreeWidgetItem * item, int column);
	
	private:
		void closeEvent(QCloseEvent * e);
		void updateStatus(QTreeWidgetItem * node);
		void visibilityChange();
		void appendConsole(QString text);
		void createTrayActions();
		
		bool checkSubNode(QTreeWidgetItem * node);
		
		Ui::MainWindow *ui;
		PgreSqlDrv * _db;
		ScheduleList _scl;
		QSystemTrayIcon * _tray;
		Qt::WindowStates _state;
		QSettings * settings;
};

#endif // MAINWINDOW_H
