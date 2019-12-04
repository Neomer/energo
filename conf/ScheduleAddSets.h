#ifndef SCHEDULEADDSETS_H
#define SCHEDULEADDSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"


namespace Ui {
	class ScheduleAddSets;
}

class ScheduleAddSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit ScheduleAddSets(QWidget *parent, 
								 PgreSqlDrv * connection, 
								 QTreeWidgetItem * item);
		~ScheduleAddSets();
		
	private slots:
		void dropChanges();
		void saveChanges();
		void appendChild();
		
	signals:
		void onCreateChild(QTreeWidgetItem * item);
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
	
	private:
		void updateForm();
		PgreSqlDrv * m_connection;
		QTreeWidgetItem * m_node;
		Ui::ScheduleAddSets *ui;
};

#endif // SCHEDULEADDSETS_H
