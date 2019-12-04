#include "ReportTable.h"
#include <QPen>
#include <QMessageBox>
#include "ReportText.h"

ReportTable::ReportTable() :
	ReportElement(RET_Table)
{
	_rowheight = 20;
	_left = 0;
	_top = 0;
	_width = 40;
	_item = new QGraphicsRectItem(QRect(0, 0, _width, _rowheight));
}

ReportTable::ReportTable(int rows, int columns) :
	ReportElement(RET_Table)
{
	_rowheight = 20;
	_left = 0;
	_top = 0;
	_width = 40;
	_item = new QGraphicsRectItem(QRect(0, 0, _width, rows * _rowheight));

	for (int r = 0; r < rows; r++)
	{
		ReportTableRow * row = new ReportTableRow(r, columns, r * _rowheight, _item);
		row->setHeight(_rowheight);
		_rows.append(row);		
	}
	_size = QSize(_width, rows * _rowheight);
}

ReportTable::ReportTable(QTableWidget *twdgt) :
	ReportElement(RET_Table)
{
	int rows = twdgt->rowCount() + 1,
			columns = twdgt->columnCount();
	
	_rowheight = 20;
	_left = 0;
	_top = 0;
	_width = 40;
	_item = new QGraphicsRectItem(QRect(0, 0, _width, rows * _rowheight));

	for (int r = 0; r < rows; r++)
	{
		ReportTableRow * row = new ReportTableRow(r, columns, r * _rowheight, _item);
		row->setHeight(_rowheight);
		_rows.append(row);		
	}
	_size = QSize(_width, rows * _rowheight);

	QFont bold = QFont();
	bold.setBold(true);
	for (int c = 0; c < twdgt->columnCount(); c++)
	{
		if (twdgt->horizontalHeaderItem(c))
		{
			cell(0, c)->setElement(new ReportText(
									   twdgt->horizontalHeaderItem(c)->text(),
									   bold,
									   Qt::AlignCenter
									   ));
			cell(0, c)->setColor(twdgt->horizontalHeaderItem(c)->background());
		}
	}	
	for (int r = 1; r < twdgt->rowCount() + 1; r++)
	{
		for (int c = 0; c < twdgt->columnCount(); c++)
		{
			int row = r - 1;
			if (twdgt->item(row, c))
			{
				cell(r, c)->setElement(new ReportText(
										   twdgt->item(row, c)->text(), 
										   twdgt->item(row, c)->font(), 
										   Qt::AlignLeft));
				cell(r, c)->setColor(twdgt->item(row, c)->background());
			}
		}
	}
}

QGraphicsRectItem *ReportTable::graphicsItem()
{
	return _item;
}

double ReportTable::height()
{
	double height = 0;
	for (int i = 0; i < _rows.count(); i++)
	{
		height += _rows.at(i)->height();
	}
	
	return height;
}

void ReportTable::setWidth(double width)
{
	_width = width;
	_item->setRect(_item->rect().left(), _item->rect().top(), _width, _item->rect().height());
	_item->setToolTip(QString("%1 - %2 - %3").arg(
						  QString::number(_width),
						  QString::number(_item->boundingRect().width()),
						  QString::number(_item->pen().width() * 2)));
	foreach (ReportTableRow * r, _rows)
	{
		r->setWidth(_item->boundingRect().width() - _item->pen().widthF() * 2);
	}
	_size.setWidth(_width);
}

void ReportTable::setPos(double x, double y)
{
	_left = x;
	_top = y;
	_item->setPos(x, y);
}

void ReportTable::setRowHeight(double value)
{
	_rowheight = value;
	foreach (ReportTableRow * r, _rows)
	{
		r->setHeight(value);
	}
	_size.setHeight(_rows.count() * _rowheight);
}

void ReportTable::setRowHeight(int index, double value)
{
	ReportTableRow * r = row(index);
	if (!r)
		return;
	double diff = r->height() - value;
	r->setHeight(value);
	for (int i = index + 1; i < _rows.count(); i++)
	{
		ReportTableRow * rr = _rows[i];
		rr->setTop(rr->top() - diff);
	}
	_item->setRect(_item->rect().left(), _item->rect().top(), _width, _item->rect().height() - diff);	
	_size.setHeight(_size.height() - diff);
}

void ReportTable::setColumnWidth(int index, double value)
{
	if (_rows.count() == 0)
		return;
	
	double width = _width;
	
	for (int i = 0; i < index; i++)
	{
		width -=_rows.at(0)->column(i)->element()->width();
	}
	
	_size.setWidth(_size.width() + _rows.at(0)->column(index)->element()->width() - value);

	double diff = (width - value) / (_rows.at(0)->columnCount() - index  - 1);

	foreach (ReportTableRow * r, _rows)
	{
		r->column(index)->element()->setWidth(value);
		for (int i = index + 1; i < r->columnCount(); i++)
		{
			r->column(i)->element()->setWidth(diff);
			
			r->column(i)->element()->setPos(
						r->column(i - 1)->element()->pos().x() + r->column(i - 1)->element()->width(), 
						r->column(i - 1)->element()->pos().y());
			
		}
	}
}

ReportTableElement *ReportTable::cell(int row, int column)
{
	if ((row < 0) || (row >= _rows.count()))
		return 0;
	
	ReportTableColumn * clmn = _rows[row]->column(column);
	if (clmn == 0)
		return 0;
	
	return clmn->element();
}

ReportTableRow *ReportTable::row(int index)
{
	if ((index < 0)||(index >= _rows.count()))
		return 0;
	return _rows[index];
}
