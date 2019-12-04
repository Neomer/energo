#ifndef ABSTRACTREPORTPLUGIN_H
#define ABSTRACTREPORTPLUGIN_H

#include <QWidget>
#include <QObject>
#include <QString>
#include "../pgredrv/PgreSqlDrv.h"
#include "../ReportEngine/ReportEngine.h"

class AbstractReportPlugin
{
	public:
		virtual void load(PgreSqlDrv * connection, QWidget * window) = 0;
		virtual void unload() = 0;
		virtual QString getName() = 0;
		virtual QString getVersion() = 0;
		virtual void getPrintableForm(ReportEngine * engine) = 0;
	
		virtual ~AbstractReportPlugin() {}
};

Q_DECLARE_INTERFACE(AbstractReportPlugin,
                    "com.trolltech.Plugin.AbstractReportPlugin/1.0.0");


#endif // ABSTRACTREPORTPLUGIN_H
