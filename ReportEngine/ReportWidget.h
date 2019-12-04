#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include "ReportElement.h"

#include "ReportEngine_global.h"
#include <QGraphicsItem>
#include <QWidget>
#include <QGraphicsProxyWidget>

class REPORTENGINESHARED_EXPORT ReportWidget : public ReportElement
{
	public:
		ReportWidget(QWidget * widget);
		
		double height();
		
		void setWidth(double value);
		void setPos(double x, double y);
		
		QWidget * widget();
		void setGraphicsItem(QGraphicsProxyWidget * item);
		
		QGraphicsItem * graphicsItem();
		
	private:
		QWidget * _wdgt;
		double _left;
		double _top;
		double _width;
		double _height;
		QGraphicsProxyWidget * _item;
};

#endif // REPORTWIDGET_H
