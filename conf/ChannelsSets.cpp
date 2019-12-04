#include "ChannelsSets.h"
#include "ui_ChannelsSets.h"
#include "struct_desc.h"

#include <QGroupBox>
#include <QMessageBox>
#include "ListPicker.h"

ChannelsSets::ChannelsSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item) :
	QWidget(parent),
    ui(new Ui::ChannelsSets)
{
    ui->setupUi(this);
	m_connection = connection;
	
	this->m_connection = connection;
	this->m_id = id;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setWindowTitle(tr("Способ соединения"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);

	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
	
}

ChannelsSets::~ChannelsSets()
{
	delete ui;
}

void ChannelsSets::onSave()
{
	
}

void ChannelsSets::onReset()
{
	
}

void ChannelsSets::onTypeSelect()
{
	
}

void ChannelsSets::onTypeChange(int row)
{
	
}

void ChannelsSets::onRemoveItem()
{
	
}

void ChannelsSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdRemove->setEnabled(false);
		m_type = 1;
	}
	else
	{
		ui->cmdRemove->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select c.index, c.name, ct.id typeid, ct.name typename from channel c left join channel_type ct on ct.id=c.type where c.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("ChannelSets::CounterSets() - Channel not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtNumber->setText(res->getValue("index"));
			ui->txtName->setText(res->getValue("name"));
			ui->txtType->setText(res->getValue("typename"));
			m_type = res->getValue("typeid").toInt();
		}
		res->close();
	}
}
