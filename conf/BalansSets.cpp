#include "BalansSets.h"
#include "ui_BalansSets.h"
#include <QMessageBox>
#include <QGroupBox>
#include "struct_desc.h"

#include "BalansSelectElements.h"

BalansSets::BalansSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::BalansSets)
{
    ui->setupUi(this);
	QGroupBox * gb = (QGroupBox *)parent;
	
	_conn = connection;
	_id = id;
	_node = item;
	
	gb->setTitle(tr("Настройки группы:"));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	updateData();
	
	connect(ui->cmdRemove, SIGNAL(clicked(bool)), this, SLOT(removeItem()));
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
}

BalansSets::~BalansSets()
{
    delete ui;
}

void BalansSets::updateData()
{
	if (_id == -1)
	{
		ui->cmdAdd->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
	}
	else
	{
		ui->cmdAdd->setEnabled(true);
		ui->cmdRemove->setEnabled(true);

		PgreSqlResult * res = this->_conn->exec(tr("select * from balans where id=%1 limit 1;").arg(QString::number(_id)));
		
		if (!res->hasRows())
		{
			qDebug("BalansSets::updateForm() - Balans not found!\n\tID: %d", _id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
		}
		
		res->close();
		updateChannelList();
	}
}

void BalansSets::updateChannelList()
{
	if (_id != -1)
	{
		ui->twElements->clear();
		PgreSqlResult * res = _conn->exec(QString("select ft.name as factory, o.name as object, f.name as feeder, c.c_number as counter, ch.name as channel, b.direction, ch.id as ch_id from balans_element b left join channel ch on ch.id=b.channel left join counter c on c.id=ch.counter left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where b.balans=%1 order by ft.name, o.name, f.name, c.c_number, ch.name, b.direction;").arg(_id));
		QTableWidgetItem * twi;
		
		QStringList hdr;
		hdr.append(tr("Предприятие"));
		hdr.append(tr("Подстанция"));
		hdr.append(tr("Фидер"));
		hdr.append(tr("Счетчик"));
		hdr.append(tr("Канал"));
		hdr.append(tr("Направление"));
		
		ui->twElements->setColumnCount(hdr.count());
		ui->twElements->setHorizontalHeaderLabels(hdr);
		ui->twElements->setRowCount(res->numRows());
		
		while (res->notEoF())
		{
			for (int f = 0; f < res->numFields() - 1; f++)
			{
				twi = new QTableWidgetItem();
				twi->setText(res->getValue(f));
				twi->setData(Qt::UserRole, QVariant::fromValue(res->getValue("ch_id").toInt()));
				ui->twElements->setItem(res->absolutePos(), f, twi);
			}
			res->moveNext();
		}
		res->close();
	}
}

void BalansSets::removeItem()
{
	if (_id == -1)
		return;
	
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить группу?").append(this->_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql = "delete from balans where id=%1;";
		if (_conn->exec(sql.arg(QString::number(_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->cmdRemoveBalans->setEnabled(false);
			ui->cmdAdd->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			ui->twElements->setEnabled(false);
			_id = -1;
			emit onRemove(this->_node);
			delete this->_node;
		}
		else
		{
			qDebug("BalansSets::removeItem() - SQL ERROR: %s\n%s",
				   _conn->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить балансовую группу. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void BalansSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		if (_id != -1)
		{
			sql = "update balans set name='%1' where id=%2;";
			sql = sql.arg(ui->txtName->text(), QString::number(_id));
		}
		else
		{
			sql = "insert into balans (name) values ('%1') returning id;";
			sql = sql.arg(ui->txtName->text());
		}
		PgreSqlResult * r;
		if (!(r = _conn->exec(sql))->isValid())
		{
			qDebug("BalansSets::saveChanges() - SQL ERROR: %s\n%s", 
			       _conn->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			_node->setText(0, ui->txtName->text());
			if (_id == -1)
			{
				TVItemDesc d = _node->data(0, Qt::UserRole).value<TVItemDesc>();
				Factory * f = (Factory *)d.link;
				_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(_node);
		}
	}
	updateData();
}

void BalansSets::dropChanges()
{
	updateData();
}

void BalansSets::addChannels()
{
	BalansSelectElements * bse = new BalansSelectElements(_conn, _id, this);
	bse->setWindowTitle(tr("Выбор элементов баланса"));
	connect(bse, SIGNAL(onUpdate()), this, SLOT(updateChannelList()));
	bse->show();
}

void BalansSets::removeChannels()
{
	if (ui->twElements->selectedItems().count() == 0)
		return;
	
	int id = ui->twElements->selectedItems().at(0)->data(Qt::UserRole).value<int>();
	PgreSqlResult * r = _conn->exec(QString("delete from balans_element where balans=%1 and channel=%2").arg(QString::number(_id), QString::number(id)));
	if (!r->isValid())
	{
		qDebug("BalansSets::removeChannels() - SQL ERROR: %s",
			   _conn->getError().toAscii().constData());
		QMessageBox::critical(this, tr("Балансовые группы"), tr("Ошибка запроса к БД!"));
	}
	updateChannelList();
}
