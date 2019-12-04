#ifndef CHGSETS_H
#define CHGSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
class CHGSets;
}

class CHGSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit CHGSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~CHGSets();
		
	private slots:
		void dropChanges();
		void saveChanges();
		//void appendChild();
		
	signals:
		void onCreateChild(QTreeWidgetItem * item);
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
	
	private:
		void updateForm();
		PgreSqlDrv * m_connection;
		QTreeWidgetItem * m_node;
		int m_id;
		Ui::CHGSets *ui;
};

#endif // CHGSETS_H
