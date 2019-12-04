#ifndef PLANNINGMW_H
#define PLANNINGMW_H

#include <QMainWindow>
#include <QSettings>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>
#include <QTableWidgetItem>
#include <QDate>

#define MAIN_TITLE		tr("Energo - Планирование")

namespace Ui {
	class PlanningMW;
}

class PlanningMW : public QMainWindow
{
		Q_OBJECT
		
	public:
		explicit PlanningMW(QSettings * settings, QWidget *parent = 0);
		~PlanningMW();
		
	public slots:
		void loginFormClosed();
		void databaseConnected(PgreSqlDrv * connection, int uid);
		
	private slots:
		void updateTree();
		void dpgSelected(QTreeWidgetItem * item, int column);
		void updateTable();
		void checkInputValue(QTableWidgetItem * item);
		void saveChanges();
		void dateChanged(QDateTime date);
		void exportToExcel();
		void measuringLengthChange(int index);
		
	private:
		Ui::PlanningMW *ui;
		QSettings * _settings;
		PgreSqlDrv * _connection;
		int _uid;
		QDate _date;
};

#endif // PLANNINGMW_H
