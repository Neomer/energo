#include "FeederSets.h"
#include "ui_FeederSets.h"
#include <QGroupBox>
#include <QMessageBox>
#include "struct_desc.h"
#include "transformerexchange.h"

FeederSets::FeederSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::FeederSets)
{
    ui->setupUi(this);

	this->m_id = id;
	this->m_connection = connection;
	this->m_node = item;
	
    PgreSqlResult * res = this->m_connection->exec("select * from voltage_level_type order by name;");
    while (res->notEoF())
    {
        ui->cmbVoltageLVL->addItem(res->getValue("name"), res->getValue("id").toInt());
        res->moveNext();
    }
   
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки фидера:"));
    
    connect(ui->cmdChangeTrans, SIGNAL(clicked(bool)), this, SLOT(transExchange()));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	ui->cmdAddCounter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	/*
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
	*/
	
    
	ui->txtName->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Zа-яА-Я\\s\\d.-]{1,25}$"), ui->txtName));
	ui->txtKNh->setValidator(new QRegExpValidator(QRegExp("^\\d{1,7}$"), ui->txtKNh));
	ui->txtKNl->setValidator(new QRegExpValidator(QRegExp("^\\d{1,7}$"), ui->txtKNl));
	ui->txtKTh->setValidator(new QRegExpValidator(QRegExp("^\\d{1,7}$"), ui->txtKTh));
	ui->txtKTl->setValidator(new QRegExpValidator(QRegExp("^\\d{1,7}$"), ui->txtKTl));
}

FeederSets::~FeederSets()
{
    delete ui;
}

void FeederSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdAddCounter->setEnabled(false);
		ui->cmdRemove->setEnabled(false);
	}
	else
	{
		ui->cmdAddCounter->setEnabled(true);
		ui->cmdRemove->setEnabled(true);
		PgreSqlResult * res = m_connection->exec(tr("select * from feeder f where f.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("FeederSets::updateForm() - Feeder not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtName->setText(res->getValue("name"));
			ui->txtKNh->setText(res->getValue("kn_h"));
			ui->txtKNl->setText(res->getValue("kn_l"));
			ui->txtKTh->setText(res->getValue("kt_h"));
			ui->txtKTl->setText(res->getValue("kt_l"));
            int lvl = res->getValue("v_lvl").toInt();
            for (int i = 0; i < ui->cmbVoltageLVL->count(); i++)
            {
                if (ui->cmbVoltageLVL->itemData(i).toInt() == lvl)
                {
                    ui->cmbVoltageLVL->setCurrentIndex(i);
                    break;
                }
            }
		}
		res->close();
	}
}

/************************************************
  
		SLOTS
		
*************************************************/
void FeederSets::dropChanges()
{
	updateForm();
}

void FeederSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		PgreSqlResult * r;
		if (m_id != -1)
		{
			sql = QString("select kt_h, kt_l, kn_h, kn_l, (kt_h / kt_l * kn_h / kn_l) as kt from feeder where id=%1").arg(QString::number(m_id));
			r = m_connection->exec(sql);
			if ((ui->txtKNh->text().toInt() != r->getValue("kn_h").toInt()) ||
					(ui->txtKNl->text().toInt() != r->getValue("kn_l").toInt()) ||
					(ui->txtKTh->text().toInt() != r->getValue("kt_h").toInt()) ||
					(ui->txtKTl->text().toInt() != r->getValue("kt_l").toInt()))
			{
				res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Пересчитать профили с новыми коэффициентами?\nВНИМАНИЕ! Может занять очень продолжительное время!"), QMessageBox::Yes, QMessageBox::No);
				if (res == QMessageBox::Yes)
				{
					double Kt = ((ui->txtKTh->text().toInt() / ui->txtKTl->text().toInt()) * (ui->txtKNh->text().toInt() / ui->txtKNl->text().toInt())) / 
							r->getValue("kt").toDouble();
					sql = QString("update data set value=value*%1 where feeder=%2").arg(QString::number(Kt, 'f'), QString::number(m_id));
					r = m_connection->exec(sql);
					if (!r->isValid())
					{
						qDebug("FeederSets::saveChanges() - SQL ERROR: %s\n%s", 
						       m_connection->getError().toAscii().constData(),
						       sql.toAscii().constData());
						QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно пересчитать данные!"));
					}
				}
			}
			
			sql = "update feeder set name='%1', kt_h=%2, kt_l=%3, kn_h=%4, kn_l=%5, v_lvl=%6 where id=%7;";
			sql = sql.arg(
                        ui->txtName->text(),
                        ui->txtKTh->text(), 
                        ui->txtKTl->text(), 
                        ui->txtKNh->text(), 
                        ui->txtKNl->text(),
                        QString::number(ui->cmbVoltageLVL->itemData(ui->cmbVoltageLVL->currentIndex()).toInt()),
                        QString::number(m_id));
		}
		else
		{
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Object * f = (Object *)d.link;
			sql = "insert into feeder (name, kt_h, kt_l, kn_h, kn_l, object) values ('%1', %2, %3, %4, %5, %6) returning id;";
			sql = sql.arg(ui->txtName->text(), ui->txtKTh->text(), ui->txtKTl->text(), ui->txtKNh->text(), ui->txtKNl->text(), QString::number(f->ID));
		}
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("FeederSets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Feeder * f = (Feeder *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->name = ui->txtName->text();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void FeederSets::removeFeeder()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить фидер: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		// Удаляем данные по фидеру
		QString sql = "delete from data where feeder=%1;";
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить фидер. Подробнее об ошибке см. в логах."));
			return;
		}
		
		// Удаляем счетчики, привязанные к фидеру
		sql = "delete from counter where feeder=%1;";
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить фидер. Подробнее об ошибке см. в логах."));
			return;
		}

		// Удаляем фидер
		sql = "delete from feeder where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtName->setEnabled(false);
			ui->txtKNh->setEnabled(false);
			ui->txtKNl->setEnabled(false);
			ui->txtKTh->setEnabled(false);
			ui->txtKTl->setEnabled(false);
			ui->cmdAddCounter->setEnabled(false);
			ui->cmdDrop->setEnabled(false);
			ui->cmdSave->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			m_id = -1;
			emit onRemove(m_node);
			delete m_node;
		}
		else
		{
			qDebug("FeederSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить фидер. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void FeederSets::appendChild()
{
    emit onCreateChild(m_node);
}

void FeederSets::transExchange()
{
    TransformerExchange te(this, this->m_connection, m_id);
    te.exec();
}
