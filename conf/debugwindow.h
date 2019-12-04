#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QObject>
#include <QDialog>
#include <QIODevice>
#include <QDir>
#include <QDateTime>
#include <QFile>

#include "debugreader.h"

namespace Ui {
    class DebugWindow;
}

class DebugWindow : public QDialog
{
    Q_OBJECT

public:
    DebugWindow(QWidget *parent = 0);
    ~DebugWindow();

	void addRow(QString text);

private:
    Ui::DebugWindow *ui;
	QFile *log_file;
};

#endif // DEBUGWINDOW_H
