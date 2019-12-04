#ifndef REPORTENGINEPLUGIN_H
#define REPORTENGINEPLUGIN_H

#include "ReportEngine.h"

class ReportEnginePlugin : public ReportEngine
{
	Q_INTERFACES(ReportEngine)
	
public:
	ReportEnginePlugin();
	bool loadSource(QString &filename);
	
	void setWidget(QWidget *widget);
	QWidget * widget();
	
	void setDBConnection(PGconn *connection);
	PGconn * dbConnection();
	
	bool display();
	bool display(QWidget * widget);

private:
	QString m_filename;
	QWidget * m_widget;
	PGconn * m_conn;
	
};

#endif // REPORTENGINEPLUGIN_H
