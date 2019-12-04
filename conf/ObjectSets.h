#ifndef OBJECTSETS_H
#define OBJECTSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class ObjectSets;
}

class ObjectSets : public QWidget
{
    Q_OBJECT

public:
    ObjectSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
    ~ObjectSets();

private slots:
	void dropChanges();
	void saveChanges();
	void removeItem();
	void appendChild();
	void connectionChange(int row);
	void connectionChangeRequest();
	
signals:
	void onCreateChild(QTreeWidgetItem * item);
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);
	
	
private:
	void updateForm();
	Ui::ObjectSets *ui;
	PgreSqlDrv * m_connection;
	int m_id;
	QTreeWidgetItem * m_node;
};

#endif // OBJECTSETS_H
