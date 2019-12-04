#ifndef MANUALINPUTRPT_H
#define MANUALINPUTRPT_H

#include "manualinputrpt_global.h"
#include <QObject>
#include "../../includes/AbstractReportPlugin.h"
#include "../../pgredrv/PgreSqlDrv.h"
#include "ui_ManualInputForm.h"
#include <QTreeWidgetItem>

#define REPORT_NAME	tr("Ручной ввод")
#define REPORT_VER	tr("1.1.0")

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

class ManualInputRpt  : public QObject, public AbstractReportPlugin
{
	Q_OBJECT
	Q_INTERFACES(AbstractReportPlugin)
	
	public:
		ManualInputRpt();
		// Переопределенные функции
		void load(PgreSqlDrv *connection, QWidget *window);
		void unload();
		QString getName();
		QString getVersion();
		void getPrintableForm(ReportEngine *engine);
		
	private slots:
		void updateTree(QTreeWidgetItem * parent, int column);
		void loadData();
		void dateBeginChanged(QDateTime dt);
		void dateEndChanged(QDateTime dt);
		void intervalTypeChanged(int index);
		void dtBeginContexMenuReq(QPoint position);
		void dtEndContexMenuReq(QPoint position);
		void setdtBeginDayBegin();
		void setdtEndDayBegin();
		
	private:
		enum DateAutoSet
		{
			DAS_DAY,
			DAS_CURRMONTH,
			DAS_NEXTMONTH
		};
		void CreateUi();
        PgreSqlDrv * m_connection;
        QWidget * m_parent;
        Ui::ManualInputForm * ui;
};

#endif // MANUALINPUTRPT_H
