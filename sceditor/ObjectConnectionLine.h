#ifndef OBJECTCONNECTIONLINE_H
#define OBJECTCONNECTIONLINE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QPen>

#include "SchemeObject.h"

class ObjectConnectionLine : public SchemeObject
{
	public:
		ObjectConnectionLine(SchemeObject * first = 0, SchemeObject * second = 0);
		~ObjectConnectionLine();

		QRectF boundingRect() const;

		void paint(QPainter *painter,
				   const QStyleOptionGraphicsItem *option,
				   QWidget *widget);


		void setFirst(SchemeObject * first);
		SchemeObject * first();

		void setSecond(SchemeObject * second);
		SchemeObject * second();

		QGraphicsLineItem * line();

		SchemeObject * other(SchemeObject * test);

		void updateObject();

		
		void setWidth(double width);
		double width();

		void setHeight(double height);
		double height();
		
	protected:
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

	private:
		SchemeObject * _first, * _second;
		QGraphicsLineItem * _line;
		double _border_w;
		double _width, _height;
		QBrush _brush;
		QList<QPointF> _corners;
};

#endif // OBJECTCONNECTIONLINE_H
