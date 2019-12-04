#include "ListPicker.h"
#include "ui_ListPicker.h"

ListPicker::ListPicker(QWidget *parent, PgreSqlResult *res, int id) :
    QDialog(parent),
    ui(new Ui::ListPicker)
{
    ui->setupUi(this);
	this->m_id = id;
	this->m_result = res;
	if (this->layout()) delete this->layout();
	this->setLayout(ui->mainLayout);
	
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setModal(true);
	
	ui->twList->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(ui->twList, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemSelected(int,int)));
	
	ui->twList->setColumnCount(res->numFields());
	ui->twList->setRowCount(res->numRows());
	ui->twList->setHorizontalHeaderLabels(res->getFields());
	
	while (res->notEoF())
	{
		for (int f = 0; f < res->numFields(); f++)
		{
			QTableWidgetItem * item = new QTableWidgetItem();
			item->setText(res->getValue(f));
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ui->twList->setItem(res->absolutePos(), f, item);
		}
		res->moveNext();
	}
	ui->twList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui->twList->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	if (ui->twList->rowCount() > 0) ui->twList->selectRow(0);
}

ListPicker::ListPicker(QWidget *parent, PgreSqlResult *res, QStringList columns, int id) :
    QDialog(parent),
    ui(new Ui::ListPicker)
{
    ui->setupUi(this);
	this->m_id = id;
	this->m_result = res;
	if (this->layout()) delete this->layout();
	this->setLayout(ui->mainLayout);
	this->setModal(true);
	
	this->setAttribute(Qt::WA_DeleteOnClose);
	
	ui->twList->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(ui->twList, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(itemSelected(int,int)));
	
	ui->twList->setColumnCount(res->numFields());
	ui->twList->setRowCount(res->numRows());
	ui->twList->setHorizontalHeaderLabels(columns);
	
	while (res->notEoF())
	{
		for (int f = 0; f < res->numFields(); f++)
		{
			QTableWidgetItem * item = new QTableWidgetItem();
			item->setText(res->getValue(f));
			item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			ui->twList->setItem(res->absolutePos(), f, item);
		}
		res->moveNext();
	}
	ui->twList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	ui->twList->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	if (ui->twList->rowCount() > 0) ui->twList->selectRow(0);
}

ListPicker::~ListPicker()
{
    delete ui;
}

void ListPicker::itemSelected(int row, int column)
{
	emit onPick(row);
	close();
}

void ListPicker::okPressed()
{
	QTableWidgetItem * item = ui->twList->selectedItems().at(0);
	itemSelected(item->row(), item->column());
}

PgreSqlResult * ListPicker::getQuery()
{
	return m_result;
}
