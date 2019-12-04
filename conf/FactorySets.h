#ifndef FACTORYSETS_H
#define FACTORYSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class FactorySets;
}

class FactorySets : public QWidget
{
    Q_OBJECT

public:
    FactorySets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
    ~FactorySets();
	
private slots:
	void dropChanges();
	void saveChanges();
	void removeItem();
	void appendChild();
	
signals:
	void onCreateChild(QTreeWidgetItem * item);
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);
	

private:
    Ui::FactorySets *ui;
	void updateForm();
	PgreSqlDrv * m_connection;
	int m_id;
	QTreeWidgetItem * m_node;
};

#endif // FACTORYSETS_H
