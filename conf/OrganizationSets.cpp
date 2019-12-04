#include "OrganizationSets.h"
#include "ui_OrganizationSets.h"
#include <QGroupBox>
#include <QMessageBox>
#include "struct_desc.h"

OrganizationSets::OrganizationSets(QWidget *parent, PgreSqlDrv *connection, QTreeWidgetItem * item) :
    QWidget(parent),
    ui(new Ui::OrganizationSets)
{
    ui->setupUi(this);
	
	this->m_connection = connection;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки организации:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);

	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
}

OrganizationSets::~OrganizationSets()
{
    delete ui;
}

void OrganizationSets::updateForm()
{
	PgreSqlResult * res = this->m_connection->exec(tr("select value from info where name='org_name' limit 1;"));
	
	if (!res->hasRows())
	{
		qDebug("OrganizationSets::CounterSets() - Organization name is missing\n");
	}
	else
	{
		ui->txtName->setText(res->getValue("value"));
	}
	res->close();
}

/************************************************
  
		SLOTS
		
*************************************************/
void OrganizationSets::dropChanges()
{
	updateForm();
}

void OrganizationSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		sql = "update info set value='%1' where name='org_name';";
		sql = sql.arg(ui->txtName->text());
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("FactorySets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void OrganizationSets::appendChild()
{
	emit onCreateChild(m_node);
}
