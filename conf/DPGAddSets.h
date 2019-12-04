#ifndef DPGADDSETS_H
#define DPGADDSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"


namespace Ui {
	class DPGAddSets;
}

class DPGAddSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit DPGAddSets(QWidget *parent, PgreSqlDrv * connection, QTreeWidgetItem * item);
		~DPGAddSets();

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
		Ui::DPGAddSets *ui;
};

#endif // DPGADDSETS_H
