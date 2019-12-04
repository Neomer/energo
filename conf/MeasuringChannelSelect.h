#ifndef MEASURINGCHANNELSELECT_H
#define MEASURINGCHANNELSELECT_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
	class MeasuringChannelSelect;
}

class MeasuringChannelSelect : public QDialog
{
		Q_OBJECT
		
	public:
		explicit MeasuringChannelSelect(QWidget *parent, int id, PgreSqlDrv * connection);
		~MeasuringChannelSelect();
	
	private slots:
		void twObjectsItemDblClicked(QTreeWidgetItem * item, int column);
		void twObjectsItemClicked(QTreeWidgetItem * item, int column);
		void itemSelect();
		void itemRemove();
		void saveChanges();
		
	signals:
		void appendChild();
		
	private:
		void updateTree(QTreeWidgetItem * item);
		PgreSqlDrv * m_connection;
		int m_id;
		Ui::MeasuringChannelSelect *ui;
};

#endif // MEASURINGCHANNELSELECT_H
