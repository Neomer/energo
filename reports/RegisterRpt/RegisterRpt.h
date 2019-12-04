#ifndef REGISTERRPT_H
#define REGISTERRPT_H

#include <QObject>
#include "registerrpt_global.h"
#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "ui_RegisterViewForm.h"

#define REPORT_NAME	tr("Реестр")
#define REPORT_VER	tr("1.1.0")


class RegisterRpt  : public QObject, public AbstractReportPlugin
{
	Q_OBJECT
	Q_INTERFACES(AbstractReportPlugin)
	
	public:
		RegisterRpt();

		// Переопределенные функции
		void load(PgreSqlDrv *connection, QWidget *window);
		void unload();
		QString getName();
		QString getVersion();
		void getPrintableForm(ReportEngine *engine);
		
	private slots:
		void loadData();
		
	private:
		void CreateUi();
        PgreSqlDrv * m_connection;
        QWidget * m_parent;
        Ui::RegisterViewForm * ui;
};

#endif // REGISTERRPT_H
