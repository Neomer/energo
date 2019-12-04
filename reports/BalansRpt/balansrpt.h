#ifndef BALANSRPT_H
#define BALANSRPT_H

#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "BalansRpt_global.h"
#include "ui_balansrptform.h"

#define REPORT_NAME	tr("Расчет баланса")
#define REPORT_VER	tr("1.1.0")

#define Y_AXIS_LEGEND_COUNT		10

#define CHG_NONE		0

enum DayType
{
	All,
	Weekday,
	Weekend
};

class BalansRpt : public QObject, public AbstractReportPlugin
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

    public slots:
        void updateList();
        void showBalansCreateDlg();
		void itemSelected(QTreeWidgetItem * item, int column);
		void dateBeginChanged(QDateTime dt);
		void dateEndChanged(QDateTime dt);
		void intervalTypeChanged(int index);
		void dtBeginContexMenuReq(QPoint position);
		void dtEndContexMenuReq(QPoint position);
		void setdtBeginDayBegin();
		void setdtEndDayBegin();
		void exportToExcel();
		void filterTriggered(bool state);
        
    private:
		enum DateAutoSet
		{
			DAS_DAY,
			DAS_CURRMONTH,
			DAS_NEXTMONTH
		};
		
		enum GroupType
		{
			GT_30min,
			GT_60min,
			GT_Day
		};
		
        PgreSqlDrv * m_connection;
        QWidget * m_parent;
        Ui::BalansRptForm * ui;
};

#endif // BALANSRPT_H
