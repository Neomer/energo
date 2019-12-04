#ifndef FEEDERSETS_H
#define FEEDERSETS_H

#include <QWidget>
#include <QTreeWidget>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class FeederSets;
}

class FeederSets : public QWidget
{
    Q_OBJECT

	public:
		FeederSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~FeederSets();
	
	private slots:
		void dropChanges();
		void saveChanges();
		void removeFeeder();
		void appendChild();
        void transExchange();
		
	signals:
		void onCreateChild(QTreeWidgetItem * item);
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
	
	private:
		void updateForm();
		Ui::FeederSets *ui;
		PgreSqlDrv * m_connection;
		int m_id;
		QTreeWidgetItem * m_node;
};

#endif // FEEDERSETS_H
