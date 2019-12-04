#ifndef OPERVIEW_H
#define OPERVIEW_H

#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "OperView_global.h"
#include "ui_operviewwidget.h"
#include <QTimer>

#define REPORT_NAME	tr("Расчитанные профили ЭЭ")
#define REPORT_VER	tr("1.1.0")

#define Y_AXIS_LEGEND_COUNT		10
#define TIMER_DEFAULT_PERIOD	10

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

class OperView : public QObject, public AbstractReportPlugin
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
		void autoUpdate();
		void periodChanged();
		
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
		Ui::OperViewWidget * ui;
		QTimer * m_timer;
};

#endif // OPERVIEW_H
