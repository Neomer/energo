#include "balanscreate.h"
#include "ui_balanscreate.h"

BalansCreate::BalansCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BalansCreate)
{
    ui->setupUi(this);
    
    this->setAttribute(Qt::WA_DeleteOnClose);
    
    if (this->layout()) delete this->layout();
    this->setLayout(ui->mainLayout);
}

BalansCreate::~BalansCreate()
{
    delete ui;
}

/***********************************************
  
    SLOTS

************************************************/
void BalansCreate::addItemBtnClicked()
{
    if (ui->twTotal->selectedItems().count() > 0)
        appendItem(ui->twTotal->selectedItems().at(0));
}

void BalansCreate::removeItemBtnClicked()
{
  
}

void BalansCreate::appendItem(QTableWidgetItem *item)
{
    int rows = ui->twSelected->rowCount();
    ui->twSelected->setRowCount(rows + 1);
    for (int i = 0; i < ui->twSelected->columnCount(); i++)
        ui->twSelected->setItem(rows, i, ui->twTotal->item(item->row(), i));
}

void BalansCreate::removeItem(QTableWidgetItem *item)
{
    
}
