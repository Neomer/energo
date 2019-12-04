#ifndef ORGANIZATIONSETS_H
#define ORGANIZATIONSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class OrganizationSets;
}

class OrganizationSets : public QWidget
{
    Q_OBJECT

public:
    OrganizationSets(QWidget *parent, PgreSqlDrv * connection, QTreeWidgetItem * item);
    ~OrganizationSets();
	
private slots:
	void dropChanges();
	void saveChanges();
	void appendChild();
	
signals:
	void onCreateChild(QTreeWidgetItem * item);
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);

private:
    Ui::OrganizationSets *ui;
	void updateForm();
	PgreSqlDrv * m_connection;
	QTreeWidgetItem * m_node;
};

#endif // ORGANIZATIONSETS_H
