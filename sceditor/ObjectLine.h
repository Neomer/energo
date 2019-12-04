#ifndef OBJECTLINE_H
#define OBJECTLINE_H

#include "SchemeObject.h"

#define OBJECT_LINE_DEFAULT_POINT1		QPointF(0, 0)
#define OBJECT_LINE_DEFAULT_POINT2		QPointF(30, 30)

class ObjectLine : public SchemeObject
{
	public:
		ObjectLine(QGraphicsItem *parent = 0);
		~ObjectLine();

		QRectF boundingRect() const;

		void paint(QPainter *painter,
				   const QStyleOptionGraphicsItem *option,
				   QWidget *widget);

		void setX1(double x);
		void setX2(double x);
		void setWidth(double width);
		double width();

		void setY1(double y);
		void setY2(double y);
		void setHeight(double height);
		double height();

		void setLine(QLineF line);

		void setPos(const QPointF &pos);
		void setPos(qreal x, qreal y);

		void updateObject();

	private:
		QBrush _brush;
		int _border_w;
		QLineF _line;
};

#endif // OBJECTLINE_H
