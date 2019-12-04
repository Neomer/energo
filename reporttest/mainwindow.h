#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>
#include <QList>

#include "../includes/pgre/libpq-fe.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

	Q_PROPERTY(QString data READ getData)
	
public:
    explicit MainWindow(QWidget *parent = 0);
	QString getData();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
