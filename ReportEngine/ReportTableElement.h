#ifndef REPORTTABLEELEMENT_H
#define REPORTTABLEELEMENT_H

#include "ReportElement.h"
#include <QGraphicsRectItem>

class REPORTENGINESHARED_EXPORT ReportTableElement : public ReportElement
{
	public:
		ReportTableElement(int row, int column, ReportElement * element, QGraphicsRectItem * parent);
		
		bool isMerged();
		ReportTableElement * parent();
		
		void merge(ReportTableElement * cell);
		
		void setWidth(double value);
		double width();
		
		void setHeight(double value);
		double height();
		
		void setPos(double x, double y);
		QPointF pos();
		
		int row();
		int column();

		void setColor(QColor color);
		void setColor(QBrush brush);
		
		void setElement(ReportElement * element);
		ReportElement * element();
		
		QGraphicsRectItem * graphicsItem();
		
	private:
		void alignElement();
		ReportTableElement * _parent;
		ReportElement * _element;
		int _row;
		int _column;
		double _width;
		double _height;
		double _left;
		double _top;
		QGraphicsRectItem * _item;
};

#endif // REPORTTABLEELEMENT_H
