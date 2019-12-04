#ifndef ALERTVIEWRPT_H
#define ALERTVIEWRPT_H

#include "AlertViewRpt_global.h"
#include "../../includes/AbstractReportPlugin.h"
#include "../../includes/Alerts.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "ui_AlertViewForm.h"

#define REPORT_NAME	tr("Просмотр событий")
#define REPORT_VER	tr("1.1.0")

class  AlertViewRpt  : public QObject, public AbstractReportPlugin
{
	Q_OBJECT
	Q_INTERFACES(AbstractReportPlugin)

	public:
		AlertViewRpt();
	
		// Переопределенные функции
		void load(PgreSqlDrv *connection, QWidget *window);
		void unload();
		QString getName();
		QString getVersion();
		void getPrintableForm(ReportEngine *engine);
		
	private slots:
		void alertTypeChanged(QTreeWidgetItem * item, int column);
		void loadData();
		
	private:
		void CreateUi();
        PgreSqlDrv * m_connection;
        QWidget * m_parent;
		QTreeWidgetItem * m_alert;
        Ui::AlertViewForm * ui;
};

#endif // ALERTVIEWRPT_H
