#ifndef BALANSADDSETS_H
#define BALANSADDSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
    class BalansAddSets;
}

class BalansAddSets : public QWidget
{
    Q_OBJECT

public:
    explicit BalansAddSets(QWidget *parent, PgreSqlDrv * connection, QTreeWidgetItem * item);
    ~BalansAddSets();

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
    Ui::BalansAddSets *ui;
};

#endif // BALANSADDSETS_H
