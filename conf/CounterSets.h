#ifndef COUNTERSETS_H
#define COUNTERSETS_H

#include <QObject>
#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"
#include "ListPicker.h"
#include "struct_desc.h"

namespace Ui {
    class CounterSets;
}

class CounterSets : public QWidget
{
    Q_OBJECT

	public:
		CounterSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~CounterSets();
	
	public slots:
		void saveChanges();
		void dropChanges();
		void typeChange(int row);
		void typeChangeRequest();
		void removeItem();
		void appendChild();
		void addParams();
        void changeManualInput(int);

	signals:
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		void onCreateChild(QTreeWidgetItem * item);

		
	private:
		Ui::CounterSets *ui;
		void updateForm();
		PgreSqlDrv * m_connection;
		int m_id;
		QTreeWidgetItem * m_node;
		QWidget * _parent;
};

#endif // COUNTERSETS_H
