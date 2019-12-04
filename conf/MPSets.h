#ifndef MPSETS_H
#define MPSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
	class MPSets;
}

class MPSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit MPSets(QWidget *parent, 
						PgreSqlDrv * connection, 
						int id, 
						QTreeWidgetItem * item);
		~MPSets();
		
	private slots:
		void dropChanges();
		void saveChanges();
		void removeItem();
		void appendChild();
		void editCodes();
		void childCreated();
		
	signals:
		void onCreateChild(QTreeWidgetItem * item);
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		

	private:
		void updateForm();
		PgreSqlDrv * m_connection;
		QTreeWidgetItem * m_node;
		int m_id;
		QWidget * m_parent;
		Ui::MPSets *ui;
};

#endif // MPSETS_H
