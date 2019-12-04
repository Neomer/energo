#include "RegisterRpt.h"
#include <QtPlugin>

Q_EXPORT_PLUGIN(RegisterRpt);

RegisterRpt::RegisterRpt()
{
}

void RegisterRpt::load(PgreSqlDrv *connection, QWidget *window)
{
	Q_INIT_RESOURCE(resources);

	this->ui = new Ui::RegisterViewForm();
    this->ui->setupUi(window);
	m_connection = connection;
    m_parent = window;
	
	CreateUi();
}

void RegisterRpt::unload()
{
}

QString RegisterRpt::getName()
{
	return REPORT_NAME;
}

QString RegisterRpt::getVersion()
{
	return REPORT_VER;
}

void RegisterRpt::getPrintableForm(ReportEngine *engine)
{
}


void RegisterRpt::CreateUi()
{
	m_parent->setWindowState(Qt::WindowNoState);
    m_parent->setWindowState(Qt::WindowMaximized);
    
    if (m_parent->layout()) delete m_parent->layout();
    m_parent->setLayout(this->ui->mainLayout);
    m_parent->setWindowTitle(REPORT_NAME);
}


void RegisterRpt::loadData()
{
}
