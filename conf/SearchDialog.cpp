#include "SearchDialog.h"
#include "ui_SearchDialog.h"

SearchDialog::SearchDialog(PgreSqlDrv *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
	m_db = db;
	
	if (this->layout()) delete this->layout();
	this->setLayout(ui->mainlLayout);
	ui->twResult->hide();
	ui->twResult->setColumnCount(3);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::search()
{
	ui->twResult->hide();
	ui->twResult->clearContents();
	QString sql = "select o.name, f.name, c.c_number from counter c left join feeder f on f.id=c.feeder left join object o on f.object=o.id where to_char(c_number, '999999999999999999') like '%1' and f.name like '%2' and o.name like '%3';";
	sql = sql.arg(ui->txtCounter->text(), ui->txtFeeder->text(), ui->txtObject->text());
	PgreSqlResult * res = m_db->exec(sql);
	
	QStringList col;
	col.append(tr("Объект"));
	col.append(tr("Фидер"));
	col.append(tr("Счетчик"));
	
	ui->twResult->setHorizontalHeaderLabels(col);
	ui->twResult->setRowCount(res->numRows());
	
	while (res->notEoF())
	{
		QTableWidgetItem * item = new QTableWidgetItem();
		item->setText(res->getValue(0));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui->twResult->setItem(res->absolutePos(), 0, item);
		item = new QTableWidgetItem();
		item->setText(res->getValue(1));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui->twResult->setItem(res->absolutePos(), 1, item);
		item = new QTableWidgetItem();
		item->setText(res->getValue(2));
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		ui->twResult->setItem(res->absolutePos(), 2, item);
		res->moveNext();
	}
	ui->twResult->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui->twResult->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui->twResult->show();
}

QString SearchDialog::getCounterMask()
{
	return ui->txtCounter->text();
}

QString SearchDialog::getFeederMask()
{
	return ui->txtFeeder->text();
}

QString SearchDialog::getObjectrMask()
{
	return ui->txtObject->text();
}

