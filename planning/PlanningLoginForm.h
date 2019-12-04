#ifndef PLANNINGLOGINFORM_H
#define PLANNINGLOGINFORM_H

#include <QDialog>
#include <QSettings>
#include "../pgredrv/PgreSqlDrv.h"

namespace Ui {
	class PlanningLoginForm;
}

class PlanningLoginForm : public QDialog
{
		Q_OBJECT
		
	public:
		explicit PlanningLoginForm(QSettings * settings, QWidget *parent = 0);
		~PlanningLoginForm();
		
	signals:
		void connectToDatabase(PgreSqlDrv * connection, int uid);
		void onClose();
		
	private slots:
		void connect2db();
	
	private:
		void closeEvent(QCloseEvent * e);
		Ui::PlanningLoginForm *ui;
		QSettings *_settings;
};

#endif // PLANNINGLOGINFORM_H
