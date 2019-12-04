#ifndef DPSETS_H
#define DPSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
	class DPSets;
}

class DPSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit DPSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~DPSets();
		
	private slots:
		void dropChanges();
		void saveChanges();
		void removeItem();
		void appendChild();
		void editCodes();
		
	signals:
		void onCreateChild(QTreeWidgetItem * item);
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		

	private:
		void updateForm();
		PgreSqlDrv * m_connection;
		QTreeWidgetItem * m_node;
		int m_id;
		Ui::DPSets *ui;
};

#endif // DPSETS_H
