#include "channelsaddsets.h"
#include "ui_channelsaddsets.h"
#include <QGroupBox>
#include <QMessageBox>

ChannelsAddSets::ChannelsAddSets(QWidget *parent, PgreSqlDrv * connection, QTreeWidgetItem * item) :
	QWidget(parent),
	ui(new Ui::ChannelsAddSets)
{
	ui->setupUi(this);
	this->m_connection = connection;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки организации:"));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
}

ChannelsAddSets::~ChannelsAddSets()
{
	delete ui;
}

void ChannelsAddSets::onSave()
{
	
}

void ChannelsAddSets::onReset()
{
	
}

void ChannelsAddSets::onRemoveItem()
{
	
}

void ChannelsAddSets::updateForm()
{
	PgreSqlResult * res = this->m_connection->exec(tr("select value from info where name='org_name' limit 1;"));
	
	if (!res->hasRows())
	{
		qDebug("ChannelsAddSets::updateForm() - Organization name is missing\n");
	}
	else
	{
		ui->txtName->setText(res->getValue("value"));
	}
	res->close();
}
