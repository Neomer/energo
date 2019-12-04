#ifndef LASTDATARPT_H
#define LASTDATARPT_H

#include "../../includes/global.h"
#include "../../includes/AbstractReportPlugin.h"

#define REPORT_NAME	tr("Последние данные")
#define REPORT_VER	tr("1.0.0")
#include <QListWidgetItem>

#include "ui_LastDataForm.h"

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

class LastDataRpt : public QObject, public AbstractReportPlugin
{
	Q_OBJECT
	Q_INTERFACES(AbstractReportPlugin)

	public:
		LastDataRpt();

		// Переопределенные функции
		void load(PgreSqlDrv *connection, QWidget *window);
		void unload();
		QString getName();
		QString getVersion();
		void getPrintableForm(ReportEngine *engine);

	private slots:
		void loadData();
		void updateTree(QTreeWidgetItem * parent, int column);
		void exportToExcel();
		
		
	private:
		void createUi();
		PgreSqlDrv * m_connection;
		QWidget * m_window;
		Ui::LastDataForm * ui;
};

#endif // LASTDATARPT_H
