#ifndef BALANSSETS_H
#define BALANSSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
    class BalansSets;
}

class BalansSets : public QWidget
{
    Q_OBJECT

public:
	explicit BalansSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
	~BalansSets();
	
private slots:
	void addChannels();
	void removeChannels();
	void saveChanges();
	void dropChanges();
	void updateChannelList();
	void removeItem();
		
signals:
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);
	void onCreateChild(QTreeWidgetItem * item);
	
private:
	void updateData();
	Ui::BalansSets *ui;
	PgreSqlDrv * _conn;
	int _id;
	QTreeWidgetItem * _node;
};

#endif // BALANSSETS_H
