#ifndef COUNTERADDPARAMSETS_H
#define COUNTERADDPARAMSETS_H

#include <QDialog>
#include <QPluginLoader>
#include "../includes/CounterInterface.h"
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
	class CounterAddParamSets;
}

class CounterAddParamSets : public QDialog
{
		Q_OBJECT
		
	public:
		explicit CounterAddParamSets(QWidget *parent, int id, PgreSqlDrv * connection);
		~CounterAddParamSets();
		
	private slots:
		void saveChanges();
		
	private:
		Ui::CounterAddParamSets *ui;
		int _id;
		PgreSqlDrv * _conn;
		QPluginLoader * _pl;
		CounterInterface2 * _intf;
		QWidget * _parent;
};

#endif // COUNTERADDPARAMSETS_H
