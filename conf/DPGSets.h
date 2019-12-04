#ifndef DPGSETS_H
#define DPGSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
	class DPGSets;
}

class DPGSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit DPGSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~DPGSets();
		
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
		Ui::DPGSets *ui;
};

#endif // DPGSETS_H
