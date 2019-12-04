#ifndef LISTPICKER_H
#define LISTPICKER_H

#include <QDialog>
#include <QStringList>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class ListPicker;
}

class ListPicker : public QDialog
{
    Q_OBJECT

public:
    ListPicker(QWidget *parent, PgreSqlResult * res, QStringList columns, int id = -1);
	ListPicker(QWidget *parent, PgreSqlResult * res, int id = -1);
    ~ListPicker();

	PgreSqlResult * getQuery();
	
signals:
	void onPick(int index);
	
private slots:
	void itemSelected(int row, int column);
	void okPressed();
	
private:
    Ui::ListPicker * ui;
	PgreSqlResult * m_result;
	int m_id;
};

#endif // LISTPICKER_H
