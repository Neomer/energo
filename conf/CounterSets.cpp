#include "CounterSets.h"
#include "ui_CounterSets.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QRegExp>
#include "CounterAddParamSets.h"

CounterSets::CounterSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem * item) :
    QWidget(parent),
    ui(new Ui::CounterSets)
{
    ui->setupUi(this);
	
	this->m_connection = connection;
	this->m_id = id;
	this->m_node = item;
	_parent = parent;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки счетчика:"));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = (QWidget *)this->children().at(i);
		w->show();
	}
	
    connect(ui->chkCounterTypeManual, SIGNAL(stateChanged(int)), this, SLOT(changeManualInput(int)));
    
	ui->cmdAddChannel->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	ui->cmdOk->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	ui->txtAddress->setValidator(new QRegExpValidator(QRegExp("^\\d{1,3}$"), ui->txtAddress));
	ui->txtDepth->setValidator(new QRegExpValidator(QRegExp("^\\d{1,3}$"), ui->txtDepth));
	ui->txtNumber->setValidator(new QRegExpValidator(QRegExp("^\\d{1,18}$"), ui->txtNumber));
	ui->txtTimeoutRead->setValidator(new QRegExpValidator(QRegExp("^\\d{1,5}$"), ui->txtTimeoutRead));
	ui->txtTimeoutWrite->setValidator(new QRegExpValidator(QRegExp("^\\d{1,5}$"), ui->txtTimeoutWrite));
	ui->txtLogin->setValidator(new QRegExpValidator(QRegExp("^\\w{1,35}$"), ui->txtLogin));
	ui->txtPassword->setValidator(new QRegExpValidator(QRegExp("^\\w{1,15}$"), ui->txtPassword));
	ui->txtMaxCorrection->setValidator(new QRegExpValidator(QRegExp("^\\d{1,3}$"), ui->txtMaxCorrection));
	ui->txtMinCorrection->setValidator(new QRegExpValidator(QRegExp("^\\d{1,3}$"), ui->txtMinCorrection));
}

CounterSets::~CounterSets()
{
    delete ui;
}

void CounterSets::updateForm()
{
	if (m_id == -1)
	{
		ui->cmdRemove->setEnabled(false);
		ui->cmdAddParam->setEnabled(false);
		ui->cmdAddChannel->setEnabled(false);
	}
	else
	{
		ui->cmdRemove->setEnabled(true);
		ui->cmdAddParam->setEnabled(true);
		ui->cmdAddChannel->setEnabled(true);
		PgreSqlResult * res = this->m_connection->exec(tr("select c.*, ct.name as typename, ct.id as typeid from counter c left join counter_type ct on c.type=ct.id where c.id=%1 limit 1;").arg(QString::number(m_id)));
		
		if (!res->hasRows())
		{
			qDebug("CounterSets::CounterSets() - Counter not found!\n\tID: %d", m_id);
		}
		else
		{
			ui->txtNumber->setText(res->getValue("c_number"));
			ui->txtAddress->setText(res->getValue("address"));
			ui->txtDepth->setText(res->getValue("max_depth"));
			ui->txtTimeoutRead->setText(res->getValue("timeout_recv"));
			ui->txtTimeoutWrite->setText(res->getValue("timeout_send"));
			ui->txtType->setText(res->getValue("typename"));
			ui->txtLogin->setText(res->getValue("login"));
			ui->txtPassword->setText(res->getValue("password"));
			ui->txtMaxCorrection->setText(res->getValue("corr_max"));
			ui->txtMinCorrection->setText(res->getValue("corr_min"));
			if (!ui->txtType->setProperty("typeid", QVariant::fromValue(res->getValue("typeid"))))
				qDebug("CounterSets::updateForm() - QEditLine property is not set!");
			ui->chkAllow->setChecked(QString(res->getValue("allow")).toInt());
			ui->chkTimeCorrection->setChecked(res->getValue("allow_corr").toInt());
		}
		res->close();
	}
}

/************************************************
  
		SLOTS
		
*************************************************/
void CounterSets::dropChanges()
{
	updateForm();
}

void CounterSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		int ch = 0;
		
		// Проверка входных значений
		PgreSqlResult * r;
        
        if (ui->chkCounterTypeManual->isChecked())
        {
            r = m_connection->exec(QString("insert into counter_type (\"name\") values ('%1') returning id;").arg(ui->txtType->text()));
            if (!r->isValid())
            {
                QMessageBox::critical(this, tr("Конфигуратор"), tr("Неверный запрос к БД. Подробнее смотрите окне отладки."));
				qDebug("CounterSets::saveChanges() - SQL ERROR: %s", 
					   m_connection->getError().toAscii().constData());
				return;
            }
            else
            {
                ui->txtType->setProperty("typeid", QVariant::fromValue(r->getValue(0)));
                ui->chkCounterTypeManual->setChecked(false);
            }
        }

		if (m_id != -1)
		{
			sql = "update counter set c_number=%1, address=%2, max_depth=%3, timeout_recv=%4, timeout_send=%5, channels=%6, type=%7, password='%8', allow=%9, login='%10', allow_corr=%12, corr_min=%13, corr_max=%14 where id=%11;";
			sql = sql.arg(
					  ui->txtNumber->text(), 
					  ui->txtAddress->text(), 
					  ui->txtDepth->text(), 
					  ui->txtTimeoutRead->text(), 
					  ui->txtTimeoutWrite->text(), 
					  QString::number(ch), 
					  ui->txtType->property("typeid").toString(), 
					  ui->txtPassword->text(), 
					  QString::number(ui->chkAllow->isChecked())).arg(
					  ui->txtLogin->text(), 
					  QString::number(m_id),
					  QString::number((int)ui->chkTimeCorrection->isChecked()),
					  ui->txtMinCorrection->text(),
					  ui->txtMaxCorrection->text());
		}
		else
		{
			sql = "select ft.name, o.name, f.name from counter c left join feeder f on f.id=c.feeder left join object o on o.id=f.object left join factory ft on ft.id=o.factory where c.c_number=%1 limit 1;";
			sql = sql.arg(ui->txtNumber->text());
			if ((r = m_connection->exec(sql))->isValid())
			{
				if (r->hasRows())
				{
					res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Номер счетчика уже используется для фидера:\n%1.\nВы уверены, что хотите сохранить текущие значения?").arg(r->getValue(0).append(" ").append(r->getValue(1).append(" ").append(r->getValue(2)))), QMessageBox::Yes, QMessageBox::No);
					if (res == QMessageBox::No)
						return;
				}
			}
			else
			{
				QMessageBox::critical(this, tr("Конфигуратор"), tr("Неверный запрос к БД. Подробнее смотрите окне отладки."));
				qDebug("CounterSets::saveChanges() - SQL ERROR: %s", 
					   m_connection->getError().toAscii().constData());
				return;
			}
			TVItemDesc d = m_node->parent()->data(0, Qt::UserRole).value<TVItemDesc>();
			Feeder * f = (Feeder *)d.link;
			sql = "insert into counter (c_number, address, max_depth, timeout_recv, timeout_send, channels, type, feeder, password, allow, login, allow_corr, corr_min, corr_max) values (%1, %2, %3, %4, %5, %6, %7, %8, '%9', %10, '%11', %12, %13, %14) returning id;";
			sql = sql.arg(
					  ui->txtNumber->text(), 
					  ui->txtAddress->text(), 
					  ui->txtDepth->text(), 
					  ui->txtTimeoutRead->text(), 
					  ui->txtTimeoutWrite->text(), 
					  QString::number(ch), 
					  ui->txtType->property("typeid").toString(), 
					  QString::number(f->ID), 
					  ui->txtPassword->text()).arg(
					  QString::number(ui->chkAllow->isChecked()), 
					  ui->txtLogin->text(),
					  QString::number(ui->chkTimeCorrection->isChecked()), 
					  ui->txtMinCorrection->text(),
					  ui->txtMaxCorrection->text());
		}

		if (!(r = m_connection->exec(sql))->isValid())
		{
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Неверный запрос к БД. Подробнее смотрите окне отладки."));
			qDebug("CounterSets::saveChanges() - SQL ERROR: %s", 
				   m_connection->getError().toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtNumber->text());
			if (ui->chkAllow->isChecked())
				m_node->setIcon(0, QIcon(":/icons/images/counter.png"));
			else
				m_node->setIcon(0, QIcon(":/icons/images/counter_innactive.png"));
			if (m_id == -1)
			{
				TVItemDesc d = m_node->data(0, Qt::UserRole).value<TVItemDesc>();
				Counter * f = (Counter *)d.link;
				m_id = f->ID = r->getValue(0).toInt();
				f->number = ui->txtNumber->text().toInt();
				m_node->setData(0, Qt::UserRole, QVariant::fromValue(d));
				qDebug("CounterSets::saveChanges() - Counter created ID: %d", m_id);
			}
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void CounterSets::typeChange(int row)
{
	ListPicker * picker = qobject_cast<ListPicker *>(sender());
	PgreSqlResult * r = picker->getQuery();
	r->moveTo(row);
	ui->txtType->setText(r->getValue("name"));
	if (!ui->txtType->setProperty("typeid", QVariant::fromValue(r->getValue("id"))))
		qDebug("CounterSets::typeChange() - QEditLine property is not set!");
}

void CounterSets::typeChangeRequest()
{
	PgreSqlResult * r = this->m_connection->exec("select id, name from counter_type order by name;");
	QStringList header;
	header.append("ID");
	header.append(tr("Наименование"));
	
	ListPicker * picker = new ListPicker(this, r, header);
	picker->setWindowTitle(tr("Тип счетчика"));
	connect(picker, SIGNAL(onPick(int)), this, SLOT(typeChange(int)));
	picker->show();
}

void CounterSets::removeItem()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Вы уверены, что хотите удалить счетчик: ").append(m_node->text(0)), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		// Удаляем данные по счетчику
		QString sql = "delete from data d using (select channels, feeder from counter where id=%1) c where ((1 << d.channel) & c.channels) != 0 and d.feeder=c.feeder;";
		if (!m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить счетчик. Подробнее об ошибке см. в логах."));
			return;
		}
		
		// Удаляем счетчик
		sql = "delete from counter where id=%1;";
		if (m_connection->exec(sql.arg(QString::number(m_id)))->isValid())
		{
			ui->txtAddress->setEnabled(false);
			ui->txtDepth->setEnabled(false);
			ui->txtNumber->setEnabled(false);
			ui->txtTimeoutRead->setEnabled(false);
			ui->txtTimeoutWrite->setEnabled(false);
			ui->cmdTypeChange->setEnabled(false);
			ui->cmdOk->setEnabled(false);
			ui->cmdCancel->setEnabled(false);
			ui->cmdRemove->setEnabled(false);
			ui->cmdAddParam->setEnabled(false);
			ui->txtMaxCorrection->setEnabled(false);
			ui->txtMinCorrection->setEnabled(false);
			ui->chkTimeCorrection->setEnabled(false);
			m_id = -1;
			delete m_node;
			emit onRemove(m_node);
		}
		else
		{
			qDebug("CounterSets::removeItem() - SQL ERROR: %s\n%s",
				   m_connection->getError().toAscii().constData(),
				   sql.toAscii().constData());
			QMessageBox::critical(this, tr("Конфигуратор"), tr("Невозможно удалить счетчик. Подробнее об ошибке см. в логах."));
			return;
		}
	}
}

void CounterSets::appendChild()
{
	emit onCreateChild(m_node);
}

void CounterSets::addParams()
{
	CounterAddParamSets * cps = new CounterAddParamSets(_parent, m_id, m_connection);
    cps->show();
}

void CounterSets::changeManualInput(int st)
{
    ui->txtType->setReadOnly((Qt::CheckState)st != Qt::Checked);
    ui->txtType->setEnabled((Qt::CheckState)st == Qt::Checked);
}
