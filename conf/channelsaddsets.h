#ifndef CHANNELSADDSETS_H
#define CHANNELSADDSETS_H


#include <QWidget>
#include <QTreeWidgetItem>

#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
class ChannelsAddSets;
}

class ChannelsAddSets : public QWidget
{
	Q_OBJECT
	
public:
	explicit ChannelsAddSets(QWidget *parent, PgreSqlDrv *connection, QTreeWidgetItem *item);
	~ChannelsAddSets();
	
public slots:
	void onSave();
	void onReset();
	void onRemoveItem();
	
signals:
	void onUpdate(QTreeWidgetItem * item);
	void onRemove(QTreeWidgetItem * item);
	
private:
	void updateForm();
	PgreSqlDrv * m_connection;
	int m_id;
	QTreeWidgetItem * m_node;
	int m_type;
	Ui::ChannelsAddSets *ui;
};

#endif // CHANNELSADDSETS_H
