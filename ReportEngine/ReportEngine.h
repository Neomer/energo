#ifndef REPORTENGINE_H
#define REPORTENGINE_H

#include <QObject>
#include <QMap>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>

#include "ReportSheet.h"

#include "ReportEngine_global.h"

class REPORTENGINESHARED_EXPORT ReportEngine : public QObject
{
	Q_OBJECT
	
	public:
		ReportEngine();
		~ReportEngine();
		
		bool loadSource(QString filename);
		void setPageSize(QSize size);
		
		void appendPage(ReportSheet * page);
		ReportSheet * appendPage();
		
		ReportSheet * sheet(int index);
		int sheetCount();
		ReportSheet * currentSheet();
		
		QFont font(QString name);
		void registerFont(QString name, QFont font);
		
		void showPrintDialog(QWidget * parent = 0);
		void showPrintPreviewDialog(QWidget * parent = 0);
		
	private:
		QList<ReportSheet *> _sheets;
		QSize _page;
		QMap<QString, QFont> _fonts;
		QPrinter * _printer;
};

Q_DECLARE_INTERFACE(ReportEngine,
                    "com.trolltech.Plugin.ReportEngine/1.0.0");

#endif // REPORTENGINE_H
