#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

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
		void appendLog(QString text);
		
	private slots:
		void visibilityChange();
		void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

	private:
		void closeEvent(QCloseEvent * event);
		void changeEvent(QEvent * event);
		Ui::MainWindow *ui;
		QSystemTrayIcon * _tray;
};

#endif // MAINWINDOW_H
