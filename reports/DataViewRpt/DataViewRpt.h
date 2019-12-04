#ifndef DATAVIEWRPT_H
#define DATAVIEWRPT_H

#include <QTextCodec>
#include <QListWidget>
#include <QTableWidget>
#include <QTreeWidgetItem>

#include "../../includes/AbstractReportPlugin.h"
#include "ui_dataviewform.h"

#define REPORT_NAME	tr("Данные по каналам учета")
#define REPORT_VER	tr("1.1.0")

#define Y_AXIS_LEGEND_COUNT		10

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
	Feeder,
	Counter,
	Channel
};

struct TreeElementDesc
{
	int id;
	TreeElementType type;
};

class DataViewRpt  : public QObject, public AbstractReportPlugin
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
		Ui::DataViewForm * ui;
};

#endif // DATAVIEWRPT_H
