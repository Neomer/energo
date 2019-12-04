#ifndef SCHEDULESETS_H
#define SCHEDULESETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QTime>

#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class ScheduleSets;
}

class ScheduleSets : public QWidget
{
    Q_OBJECT

	public:
		explicit ScheduleSets(QWidget *parent, 
							  PgreSqlDrv *connection, 
							  int id, 
							  QTreeWidgetItem * item);
		~ScheduleSets();
	
	private slots:
		void periodFactorChanged(int index);
		void shiftFactorChanged(int index);
		void periodChanged(QString value);
		void shiftChanged(QString value);
		void dropChanges();
		void saveChanges();
		void appendObjects();
		void removeObjects();
		void updateObjectList();
		void onRemove();
		
	signals:
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		
	private:
		void updateForm();
		Ui::ScheduleSets *ui;
		int _id;
		QTreeWidgetItem * _item;
		PgreSqlDrv * _conn;
		int _period;
		int _shift;
		QTime _start_time, _end_time;
		
		QWidget * _parent;
};

#endif // SCHEDULESETS_H
