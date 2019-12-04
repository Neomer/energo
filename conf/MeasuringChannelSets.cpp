#include "MeasuringChannelSets.h"
#include "ui_MeasuringChannelSets.h"
#include <QMessageBox>
#include <QGroupBox>
#include "../includes/struct_desc.h"
#include "PointCodes.h"

MeasuringChannelSets::MeasuringChannelSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
	QWidget(parent),
	ui(new Ui::MeasuringChannelSets)
{
	ui->setupUi(this);
	
	QGroupBox * gb = (QGroupBox *)parent;

	m_connection = connection;
	m_id = id;
	m_node = item;

    ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	gb->setTitle(tr("Настройки канала:"));
	
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

MeasuringChannelSets::~MeasuringChannelSets()
{
	delete ui;
}

void MeasuringChannelSets::dropChanges()
{
	updateForm();
}

void MeasuringChannelSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
			sql = "update measuringchannel set name='%1' where channel=%2;";
			sql = sql.arg(ui->txtName->text(), QString::number(m_id));
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
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void MeasuringChannelSets::removeItem()
{
    QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить канал измерения: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;

		// Удаляем завод
		sql = "delete from measuringchannel where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			emit onRemove(m_node);
			delete m_node;
		}
		else
		{
			qDebug("MeasuringChannelSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить канал измерения. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void MeasuringChannelSets::editCodes()
{
	if (m_id == -1)
		return;
	
	PointCodes * pc = new PointCodes(this, PT_Channel, m_id, m_connection);
	pc->setWindowTitle(tr("Кодировка точки  - ").append(m_node->text(0)));
	pc->exec();
}

void MeasuringChannelSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdRemove->setEnabled(false);
		ui->cmdCodes->setEnabled(false);
	}
	else
	{
		ui->cmdRemove->setEnabled(true);
		ui->cmdCodes->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select name from measuringchannel d where d.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("MeasuringChannelSets::updateForm() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
		}
		res->close();
	}
}
