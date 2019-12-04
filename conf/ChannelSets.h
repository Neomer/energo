#ifndef CHANNELSETS_H
#define CHANNELSETS_H

#include <QWidget>
#include <QTreeWidgetItem>

#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class ChannelSets;
}

class ChannelSets : public QWidget
{
    Q_OBJECT

	public:
		ChannelSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item);
		~ChannelSets();
	
	public slots:
		void onSave();
		void onReset();
		void onNameSelect();
		void onNameChange(int row);
		void onTypeSelect();
		void onTypeChange(int row);
		void onRemoveItem();
		
	signals:
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		
	private:
		Ui::ChannelSets *ui;
		void updateForm();
		PgreSqlDrv * m_connection;
		int m_id;
		QTreeWidgetItem * m_node;
		int m_type;
};

#endif // CHANNELSETS_H
