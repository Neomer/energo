#ifndef USERSETS_H
#define USERSETS_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
class UserSets;
}

class UserSets : public QWidget
{
		Q_OBJECT
		
	public:
		explicit UserSets(QWidget *parent,
						  PgreSqlDrv *connection,
						  int id,
						  QTreeWidgetItem * item);
		~UserSets();
		
	private slots:
		void itemChanged(QTreeWidgetItem * item, int column);
	
	private:
		void updateForm();
		int _id;
		QTreeWidgetItem * _item;
		PgreSqlDrv * _conn;
		QWidget * _parent;
		Ui::UserSets *ui;
};

#endif // USERSETS_H
