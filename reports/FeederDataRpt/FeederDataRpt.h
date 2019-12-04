#ifndef FEEDERDATARPT_H
#define FEEDERDATARPT_H

#include "../../includes/global.h"
#include "../../includes/AbstractReportPlugin.h"
#include "../../ReportEngine/ReportEngine.h"

#define REPORT_NAME	tr("Данные по фидерам")
#define REPORT_VER	tr("1.1.0")
#include <QListWidgetItem>

#include "ui_FeederDataForm.h"


enum IntervalType
{
	IT_Manual,
	IT_Day,
	IT_Week,
	IT_Month
};

enum TreeElementType
{
	Factory,
	Object,
	Feeder/*,
	Counter,
	Channel*/
};
struct TreeElementDesc
{
	int id;
	TreeElementType type;
};

enum SourceType
{
	Profiles = 0,
	CounterData = 1
};

enum DisplayType
{
	Summ = 0,
	OnBegin = 1,
	OnEnd = 2
};


class FeederDataRpt : public QObject, public AbstractReportPlugin
{
	Q_OBJECT
	Q_INTERFACES(AbstractReportPlugin)

	public:
		FeederDataRpt();
		
		// Переопределенные функции
		void load(PgreSqlDrv *connection, QWidget *window);
		void unload();
		QString getName();
		QString getVersion();
		void getPrintableForm(ReportEngine *engine);
	
	private slots:
		void updateList(QListWidgetItem * current, QListWidgetItem * prev);
		void loadData();
		void dateBeginChanged(QDateTime dt);
		void dateEndChanged(QDateTime dt);
		void intervalTypeChanged(int index);
		void updateTree(QTreeWidgetItem * item, int column);
		void dtBeginContexMenuReq(QPoint position);
		void dtEndContexMenuReq(QPoint position);
		void setdtBeginDayBegin();
		void setdtEndDayBegin();
		void exportToExcel();
		
	private:
		enum DateAutoSet
		{
			DAS_DAY,
			DAS_CURRMONTH,
			DAS_NEXTMONTH
		};
		void createUi();
		PgreSqlDrv * m_connection;
		QWidget * m_window;
		Ui::FeederDataForm * ui;
};

#endif // FEEDERDATARPT_H
