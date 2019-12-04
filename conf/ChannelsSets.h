#ifndef CHANNELSSETS_H
#define CHANNELSSETS_H

#include <QWidget>
#include <QTreeWidgetItem>

#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class ChannelsSets;
}

class ChannelsSets : public QWidget
{
    Q_OBJECT

public:
    ChannelsSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
    ~ChannelsSets();

	
public slots:
	void onSave();
	void onReset();
	void onTypeSelect();
	void onTypeChange(int row);
	void onRemoveItem();
	
signals:
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);
	
private:
	Ui::ChannelsSets *ui;
	void updateForm();
	PgreSqlDrv * m_connection;
	int m_id;
	QTreeWidgetItem * m_node;
	int m_type;
};

#endif // CHANNELSSETS_H
