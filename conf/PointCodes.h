#ifndef POINTCODES_H
#define POINTCODES_H

#include <QDialog>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTableWidgetItem>

namespace Ui {
	class PointCodes;
}

enum PointType
{
	PT_DPG,
	PT_DP,
	PT_MP,
	PT_Channel
};

class PointCodes : public QDialog
{
		Q_OBJECT
		
	public:
		PointCodes(QWidget *parent, PointType type, int id, PgreSqlDrv * connection);
		~PointCodes();
		
	private slots:
		void onEditClick();
		void onAddClick();
		void onRemoveClick();
		void onElementSelect(QTableWidgetItem * item);
		
	private:
		void updateList();
		Ui::PointCodes *ui;
		int _pointid;
		PointType _type;
		QWidget * _parent;
		PgreSqlDrv * _conn;
};

#endif // POINTCODES_H
