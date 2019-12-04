#include "ReportRow.h"

ReportRow::ReportRow(QGraphicsScene *scene, double top, double height, ReportSheetMargins *margins)
{
	_scene = scene;
	_top = top;
	_width = _scene->width() - margins->left() - margins->right();
	_margins = margins;
	_height = height;
}

double ReportRow::top()
{
	return _top;
}

void ReportRow::addText(QString text)
{
	addText(new ReportText(text));
}

void ReportRow::addText(QString text, QFont font)
{
	addText(new ReportText(text, font));
}

void ReportRow::addText(ReportText *item)
{
	_scene->addItem(item->graphicsItem());
	int x = _margins->left(), i;
	switch (item->alignment())
	{
		case Qt::AlignLeft:
			for (i = 0; i < _elements.count(); i++)
			{
				if (_elements.at(i)->alignment() == Qt::AlignLeft)
					x += _elements.at(i)->graphicsItem()->boundingRect().width();
			}
			if (x + item->width() > _width)
			{
				qDebug("ReportRow::addText() - Width control warning!");
			}
			item->graphicsItem()->setPos(x, _top);
			break;
			
		case Qt::AlignRight:
			for (i = 0; i < _elements.count(); i++)
			{
				if (_elements.at(i)->alignment() == Qt::AlignRight)
					_elements.at(i)->graphicsItem()->setPos(
								_elements.at(i)->graphicsItem()->pos().x() - item->graphicsItem()->boundingRect().width(), 
								_top);
			}
			item->graphicsItem()->setPos(_width - item->graphicsItem()->boundingRect().width(), _top);
			break;
			
		case Qt::AlignCenter:
			x = _width * 0.5 - item->graphicsItem()->boundingRect().width() * 0.5;
			for (i = 0; i < _elements.count(); i++)
			{
				if (_elements.at(i)->alignment() == Qt::AlignCenter)
				{
					_elements.at(i)->graphicsItem()->setPos(
								_elements.at(i)->graphicsItem()->pos().x() - item->graphicsItem()->boundingRect().width() * 0.5, 
								_top);
					x = _elements.at(i)->graphicsItem()->pos().x() + _elements.at(i)->graphicsItem()->boundingRect().width();
				}
			}
			item->graphicsItem()->setPos(x, _top);
			break;
	}
	_elements.append(item);
}

void ReportRow::addTable(ReportTable *item)
{
	_scene->addItem(item->graphicsItem());
	item->setWidth(_width);
	item->setPos(_margins->left(), _top);
	_elements.append(item);
}

void ReportRow::addWidget(ReportWidget *item)
{
	item->setGraphicsItem(_scene->addWidget(item->widget()));
	//item->setWidth(_width);
	item->setPos(_margins->left(), _top);
	_elements.append(item);
}

double ReportRow::height()
{
	double ret = _height;
	
	foreach (ReportElement * el, _elements)
	{
		switch (el->elementType())
		{
			case RET_Table:
				if (((ReportTable *)el)->height() > ret)
				{
					ret = ((ReportTable *)el)->height();
				}
				break;

			case RET_Text:
				if (((ReportText *)el)->height() > ret)
				{
					ret = ((ReportText *)el)->height();
				}
				break;

			case RET_Widget:
				if (((ReportWidget *)el)->height() > ret)
				{
					ret = ((ReportWidget *)el)->height();
				}
				break;
		}

	}

	return ret;
}
