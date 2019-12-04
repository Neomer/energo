#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "TcpConnection.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
			
		void start();
		~MainWindow();
	
	private slots:
		void connectionFailed();
		void connectionSuccess();
		void newFile(QString name);
		void progressChanged(int value);
		void updateFinish();
		
	private:
		Ui::MainWindow *ui;
		TcpConnection * _conn;
};

#endif // MAINWINDOW_H
