#include "MPSets.h"
#include "ui_MPSets.h"
#include <QMessageBox>
#include <QGroupBox>
#include "../includes/struct_desc.h"
#include "PointCodes.h"
#include "MeasuringChannelSelect.h"

MPSets::MPSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item) :
	QWidget(parent),
	ui(new Ui::MPSets)
{
	ui->setupUi(this);
	
	QGroupBox * gb = (QGroupBox *)parent;

	m_connection = connection;
	m_id = id;
	m_node = item;
	m_parent = parent;
	
	gb->setTitle(tr("Настройки точки измерения:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	updateForm();
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
}

MPSets::~MPSets()
{
	delete ui;
}
void MPSets::dropChanges()
{
	updateForm();
}

void MPSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update measuringpoint set name='%1' where id=%2;";
			sql = sql.arg(ui->txtName->text(), QString::number(m_id));
		}
		else
		{
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Feeder * f = (Feeder *)d.link;
			sql = "insert into measuringpoint (name, delp) values ('%1', %2) returning id;";
			sql = sql.arg(ui->txtName->text(), QString::number(f->ID));
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("MPSets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Factory * f = (Factory *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void MPSets::removeItem()
{
}

void MPSets::appendChild()
{
	MeasuringChannelSelect * mcs = new MeasuringChannelSelect(m_parent, m_id, m_connection);
	mcs->exec();
	connect(mcs, SIGNAL(appendChild()), this, SLOT(childCreated()));
}

void MPSets::editCodes()
{
	if (m_id == -1)
		return;
	
	PointCodes * pc = new PointCodes(this, PT_MP, m_id, m_connection);
	pc->setWindowTitle(tr("Кодировка точки  - ").append(m_node->text(0)));
	pc->exec();
}

void MPSets::childCreated()
{
	emit onCreateChild(m_node);
}

void MPSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddChannel->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
		ui->cmdCodes->setEnabled(false);
	}
	else
	{
		ui->cmdAddChannel->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		ui->cmdCodes->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select name from measuringpoint d where d.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("MPSets::updateForm() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
		}
		res->close();
	}
}
