#include "DPGSets.h"
#include "ui_DPGSets.h"
#include <QMessageBox>
#include <QGroupBox>
#include "../includes/struct_desc.h"
#include "PointCodes.h"

DPGSets::DPGSets(QWidget *parent, PgreSqlDrv * connection, int id, QTreeWidgetItem * item) :
	QWidget(parent),
	ui(new Ui::DPGSets)
{
	ui->setupUi(this);
	QGroupBox * gb = (QGroupBox *)parent;
	
	m_connection = connection;
	m_id = id;
	m_node = item;

    ui->cmdAddMeasuringPoint->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	gb->setTitle(tr("Настройки группы:"));
	
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

DPGSets::~DPGSets()
{
	delete ui;
}

void DPGSets::dropChanges()
{
	updateForm();
}

void DPGSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (m_id != -1)
		{
			sql = "update deliverypointgroup set name='%1', ndog='%2' where id=%3;";
			sql = sql.arg(
                        ui->txtName->text(), 
                        ui->txtNDog->text(),
                        QString::number(m_id));
		}
		else
		{
			sql = "insert into deliverypointgroup (name, ndog) values ('%1', '%2') returning id;";
			sql = sql.arg(ui->txtName->text(),
                          ui->txtNDog->text());
		}
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("DPGSets::saveChanges() - SQL ERROR: %s\n%s", 
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

void DPGSets::removeItem()
{
}

void DPGSets::appendChild()
{
	emit onCreateChild(m_node);
}

void DPGSets::editCodes()
{
	if (m_id == -1)
		return;
	
	PointCodes * pc = new PointCodes(this, PT_DPG, m_id, m_connection);
	pc->setWindowTitle(tr("Кодировка точки  - ").append(m_node->text(0)));
	pc->exec();
}

void DPGSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddMeasuringPoint->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
		ui->cmdCodes->setEnabled(false);
	}
	else
	{
		ui->cmdAddMeasuringPoint->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		ui->cmdCodes->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select * from deliverypointgroup d where d.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("DPGSets::updateForm() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
            ui->txtNDog->setText(res->getValue("ndog"));
		}
		res->close();
	}
}
