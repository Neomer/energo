#ifndef SCHEDULESELECTELEMENTS_H
#define SCHEDULESELECTELEMENTS_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
	class ScheduleSelectElements;
}

class ScheduleSelectElements : public QDialog
{
		Q_OBJECT
		
	public:
		explicit ScheduleSelectElements(QWidget *parent, int id, PgreSqlDrv * connection);
		~ScheduleSelectElements();

	private slots:
		void twObjectsItemDblClicked(QTreeWidgetItem * item, int column);
		void twObjectsItemClicked(QTreeWidgetItem * item, int column);
		void itemSelect();
		void itemRemove();
		void saveChanges();
		
	signals:
		void onUpdate();
		
	private:
		void updateTree(QTreeWidgetItem * item);
		PgreSqlDrv * m_connection;
		int m_id;
		Ui::ScheduleSelectElements *ui;
};

#endif // SCHEDULESELECTELEMENTS_H
