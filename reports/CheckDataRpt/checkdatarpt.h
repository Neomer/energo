#ifndef CHECKDATARPT_H
#define CHECKDATARPT_H

#include <QObject>
#include <QWidget>

#include <QTextEdit>
#include <QListView>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>

#include <QtPlugin>
#include <QTextCodec>

#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "CheckDataRpt_global.h"

#define REPORT_NAME	tr("Полнота данных")
#define REPORT_VER	tr("1.0.0")

class CheckDataRpt : public QObject, public AbstractReportPlugin
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
		
	private slots:
		void findDataDeficit();
		void refreshData();
		void sortData(int column);
		
	private:
		void updateList(PgreSqlResult * q);
		PgreSqlDrv * m_connection;
		QWidget * m_window;
		QTextCodec * m_codec;
		
		// Элементы формы
		QTableWidget * m_lv;
		QPushButton * cmdFindProblems;
		QPushButton * cmdRefresh;
		QPushButton * cmdFilter;
};

#endif // CHECKDATARPT_H
