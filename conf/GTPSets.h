#ifndef GTPSETS_H
#define GTPSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class GTPSets;
}

class GTPSets : public QWidget
{
    Q_OBJECT

public:
    GTPSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
    ~GTPSets();

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
    Ui::GTPSets *ui;
	void updateForm();
	PgreSqlDrv * m_connection;
	int m_id;
	QTreeWidgetItem * m_node;
};

#endif // GTPSETS_H
