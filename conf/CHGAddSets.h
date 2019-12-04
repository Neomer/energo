#ifndef CHGADDSETS_H
#define CHGADDSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
class CHGAddSets;
}

class CHGAddSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit CHGAddSets(QWidget *parent, PgreSqlDrv * connection, QTreeWidgetItem * item);
		~CHGAddSets();
		
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
		Ui::CHGAddSets *ui;
};

#endif // CHGADDSETS_H
