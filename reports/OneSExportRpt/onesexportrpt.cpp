#include "onesexportrpt.h"
#include <QMessageBox>

void OneSExportRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	if (!connection->isConnected())
	{
		QMessageBox::critical(window, REPORT_NAME, tr("Подключение к БД не установлено!"));
		return;
	}
	
}

void OneSExportRpt::unload()
{
	
}

QString OneSExportRpt::getName()
{
	
}

QString OneSExportRpt::getVersion()
{
	
}

void OneSExportRpt::getPrintableForm(ReportEngine *engine)
{
	
}

Q_EXPORT_PLUGIN(OneSExportRpt);
