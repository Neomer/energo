#include "ReportSheet.h"

ReportSheet::ReportSheet(QSize size)
{
	_size = size;
	_spacing = 0;
	_scene = new QGraphicsScene(0, 0, size.width(), size.height());
	_margins = ReportSheetMargins();
	addRegion(RegionMiddle);
}

QSize ReportSheet::size()
{
	return _size;
}

int ReportSheet::width() const
{
	return _size.width();
}

int ReportSheet::height() const
{
	return _size.height();
}

QGraphicsScene *ReportSheet::scene()
{
	return _scene;
}

void ReportSheet::setRegionSpacing(double value)
{
	_spacing = value;
}

int ReportSheet::regionSpacing()
{
	return _spacing;
}

void ReportSheet::addFreeElement(QPointF point, ReportElement *element)
{
	element->graphicsItem()->setPos(point);
	_scene->addItem(element->graphicsItem());
}

ReportSheetRegion * ReportSheet::addRegion(ReportSheetRegionPosition position)
{
	double top;
	double height = 50;
	foreach (ReportSheetRegion * region, _regions)
	{
		if (region->position() == position)
		{
			return region;
		}
	}
	
	ReportSheetRegion * region;
	switch (position)
	{
		case RegionTop:
			top = _margins.top();
			region = this->region(RegionMiddle);
			region->setHeight(region->height() - height);
			region->move(region->top() + height);
			break;
			
		case RegionBottom:
			region = this->region(RegionMiddle);
			region->setHeight(region->height() - height);
			top = _size.height() - _margins.bottom() - height;
			break;
			
		case RegionMiddle:
			top = _margins.top();
			height = _size.height() - _margins.vertical();
			break;
	}
	
	region = new ReportSheetRegion(position, 
								  QSize(_size.width() - _margins.horizontal(), height), 
								  top, 
								  _scene);
	region->setMargins(_margins);
	_regions.append(region);
	return region;
}

ReportSheetRegion *ReportSheet::region(ReportSheetRegionPosition position) const
{
	foreach (ReportSheetRegion * region, _regions)
	{
		if (region->position() == position)
		{
			return region;
		}
	}
	return 0;
}

void ReportSheet::setMargins(ReportSheetMargins value)
{
	// TODO: изменение полей всех дочерних объектов
	_margins = value;
}

