#include "CHGSets.h"
#include "ui_CHGSets.h"
#include <QMessageBox>
#include <QGroupBox>

CHGSets::CHGSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item) :
	QWidget(parent),
	ui(new Ui::CHGSets)
{
	ui->setupUi(this);
	ui->setupUi(this);
	this->m_connection = connection;
	this->m_node = item;
	this->m_id = id;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки организации:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
	connect(ui->cmdDrop, SIGNAL(clicked()), this, SLOT(dropChanges()));
	connect(ui->cmdSave, SIGNAL(clicked()), this, SLOT(saveChanges()));
}

CHGSets::~CHGSets()
{
	delete ui;
}

void CHGSets::dropChanges()
{
	updateForm();
}

void CHGSets::saveChanges()
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
			qDebug("CHGSets::saveChanges() - SQL ERROR: %s\n%s", 
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

void CHGSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdRemoveGroup->setEnabled(false);
		ui->cmdCreateDay->setEnabled(false);
		ui->cmdCreateMonth->setEnabled(false);
	}
	else
	{
		ui->cmdRemoveGroup->setEnabled(false);
		ui->cmdCreateDay->setEnabled(false);
		ui->cmdCreateMonth->setEnabled(false);
		PgreSqlResult * res = this->m_connection->exec(tr("select * from controlhourgroup d where d.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("CHGSets::updateForm() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
		}
		res->close();
	}
}
