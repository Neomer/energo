#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
//#include "../ReportEngine/ReportEngine.h"

class MdiWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MdiWindow(QWidget *parent = 0);
	void compile(QString filename, PgreSqlDrv * connection);
	void display();
		
private:
	QString m_report_dir;
};

#endif // MDIWINDOW_H
