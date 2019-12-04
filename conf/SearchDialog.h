#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QWidget>
#include <QDialog>

#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
    class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(PgreSqlDrv * db, QWidget *parent = 0);
    ~SearchDialog();
	
	QString getCounterMask();
	QString getFeederMask();
	QString getObjectrMask();
	

private slots:
	void search();
	
signals:
	void onSearchClick();
	
private:
    Ui::SearchDialog *ui;
	PgreSqlDrv * m_db;
};

#endif // SEARCHDIALOG_H
