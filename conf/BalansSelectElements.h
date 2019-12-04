#ifndef BALANSSELECTELEMENTS_H
#define BALANSSELECTELEMENTS_H

#include "struct_desc.h"


#include <QDialog>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

enum BalansDirection
{
	BD_Positive = 1,
	BD_Negative = -1
};

namespace Ui {
    class BalansSelectElements;
}

class BalansSelectElements : public QDialog
{
    Q_OBJECT

public:
    explicit BalansSelectElements(PgreSqlDrv * connection, int id, QWidget *parent = 0);
    ~BalansSelectElements();

private slots:
	void twListItemDblClicked(QTreeWidgetItem * item, int column);
	void twListItemClicked(QTreeWidgetItem * item, int column);
	void itemSelectPositive();
	void itemSelectNegative();
	void saveChanges();
	
signals:
	void onUpdate();	

private:
	void itemSelect(BalansDirection direction);
	QTreeWidgetItem * findTopLevelItem(QTreeWidgetItem * item, QTreeWidgetItem ** tree);
	QTreeWidgetItem * skipRepeat(QTreeWidgetItem ** item, QTreeWidgetItem * location, int * step);
	QList<QTreeWidgetItem *> treeFromTable(StructType desc, PgreSqlResult * result, BalansDirection direction);
	QList<QTreeWidgetItem *> getSelectedChannels();
	void readBranch(QList<QTreeWidgetItem *> ** list, QTreeWidgetItem * node);
    Ui::BalansSelectElements *ui;
	PgreSqlDrv * _conn;
	int _id;
};

#endif // BALANSSELECTELEMENTS_H
