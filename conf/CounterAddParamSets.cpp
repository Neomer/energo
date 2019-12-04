#include "CounterAddParamSets.h"
#include "ui_CounterAddParamSets.h"
#include <QMessageBox>
#include <QDir>

CounterAddParamSets::CounterAddParamSets(QWidget *parent, int id, PgreSqlDrv *connection) :
	QDialog(parent),
	ui(new Ui::CounterAddParamSets)
{
	ui->setupUi(this);
	
	_id = id;
	_conn = connection;
	_parent = parent;
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);
	
	PgreSqlResult * r = _conn->exec(QString("select c.c_number, c.additional, ct.name, ct.module from counter c left join counter_type ct on c.type=ct.id where c.id=%1;").arg(
										QString::number(_id)));
	
	if (!r->hasRows())
	{
		QMessageBox::critical(parent, tr("Ошибка"), tr("Указанный счетчик не существует!"));
		reject();
		return;
	}
	
	setWindowTitle(tr("Настройки доп. параметров - %1 [%2]").arg(
					   r->getValue(2),
					   r->getValue(0)));
	
	QDir dir(qApp->applicationDirPath());
	
	_pl = new QPluginLoader(dir.absoluteFilePath(r->getValue(3)));
	if (!_pl->load())
	{
		QMessageBox::critical(parent, tr("Ошибка"), tr("Невозможно загрузить драйвер устройства!"));
		reject();
		return;
	}
	
	// Загружаем поддерживаемые устройством доп. настройки
	_intf = qobject_cast<CounterInterface2 *>(_pl->instance());
	QMap<QString, AddParam> pars = _intf->getAdditionalParameters();
	
	// Переопределяем значения по умолчанию
	QString val = r->getValue(1);
	QList<QString> valp = val.split(";", QString::SkipEmptyParts);
	for (int i = 0; i < valp.count(); i++)
	{
		QList<QString> valparam = valp.at(i).split(":");
		if (valparam.count() != 2)
			continue;
		pars[valparam.at(0)].value = valparam.at(1);
	}
	
	ui->twParams->setColumnCount(2);
	ui->twParams->setRowCount(pars.count());
	
	QList<QString> keys = pars.keys();
	
	QStringList hdr;
	hdr.append(tr("Параметр"));
	hdr.append(tr("Значение"));
	
	ui->twParams->setHorizontalHeaderLabels(hdr);
	
	for (int i = 0; i < pars.count(); i++)
	{
		QTableWidgetItem * twi = new QTableWidgetItem();
		twi->setText(pars.value(keys.at(i)).description);
		twi->setFlags(Qt::ItemIsEnabled);
		twi->setData(Qt::UserRole, QVariant::fromValue(keys.at(i)));
		ui->twParams->setItem(i, 0, twi);
		
		twi = new QTableWidgetItem();
		twi->setText(pars.value(keys.at(i)).value);
		twi->setData(Qt::UserRole, QVariant::fromValue(keys.at(i)));
		ui->twParams->setItem(i, 1, twi);
	}
}

CounterAddParamSets::~CounterAddParamSets()
{
	delete ui;
}

void CounterAddParamSets::saveChanges()
{
	QString ret;
	
	for (int i = 0; i < ui->twParams->rowCount(); i++)
	{
		ret.append(QString("%1:%2;").arg(
					   ui->twParams->item(i, 1)->data(Qt::UserRole).toString(),
					   ui->twParams->item(i, 1)->text()));
	}
	if (ret != "")
	{
		PgreSqlResult * r = _conn->exec(QString("update counter set additional='%1' where id=%2;").arg(
											ret,
											QString::number(_id)));
		if (!r->isValid())
		{
			QMessageBox::critical(_parent, tr("Ошибка"), tr("Ошибка базы данных!"));
			qDebug("CounterSets::saveChanges() - SQL ERROR: %s", 
				   _conn->getError().toAscii().constData());
		}
	}
	close();
}
