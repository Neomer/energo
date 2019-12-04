#ifndef MEASURINGCHANNELSETS_H
#define MEASURINGCHANNELSETS_H

#include <QWidget>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTreeWidgetItem>

namespace Ui {
	class MeasuringChannelSets;
}

class MeasuringChannelSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit MeasuringChannelSets(QWidget *parent, 
									  PgreSqlDrv * connection, 
									  int id, 
									  QTreeWidgetItem * item);
		~MeasuringChannelSets();
		
	private slots:
		void dropChanges();
		void saveChanges();
		void removeItem();
		void editCodes();
		
	signals:
		void onUpdate(QTreeWidgetItem * item);
		void onRemove(QTreeWidgetItem * item);
		

	private:
		void updateForm();
		PgreSqlDrv * m_connection;
		QTreeWidgetItem * m_node;
		int m_id;
		Ui::MeasuringChannelSets *ui;
};

#endif // MEASURINGCHANNELSETS_H
