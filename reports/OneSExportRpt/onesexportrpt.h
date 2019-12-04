#ifndef ONESEXPORTRPT_H
#define ONESEXPORTRPT_H

#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "onesexportrpt_global.h"

#define REPORT_NAME	tr("Экспорт почасовок в 1С")
#define REPORT_VER	tr("1.1.0")

class ONESEXPORTRPTSHARED_EXPORT OneSExportRpt : public QObject, public AbstractReportPlugin
{
	Q_OBJECT 
	
	Q_INTERFACES(AbstractReportPlugin)

public:
	// Переопределенные функции
	void load(PgreSqlDrv *connection, QWidget *window);
	void unload();
	QString getName();
	QString getVersion();
	void getPrintableForm(ReportEngine *engine);

};

#endif // ONESEXPORTRPT_H
