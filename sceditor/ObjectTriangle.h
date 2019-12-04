#ifndef OBJECTTRIANGLE_H
#define OBJECTTRIANGLE_H

#include "SchemeObject.h"

#define OBJECT_TRIANGLE_DEFAULT_WIDTH		60
#define OBJECT_TRIANGLE_DEFAULT_HEIGHT		60
#define OBJECT_TRIANGLE_DEFAULT_BGCOLOR		QColor(255, 255, 255)
#define OBJECT_SELECTION_MARKER			5

class ObjectTriangle : public SchemeObject
{
	public:
		ObjectTriangle(QGraphicsItem *parent = 0);

		QRectF boundingRect() const;

		void paint(QPainter *painter,
				   const QStyleOptionGraphicsItem *option,
				   QWidget *widget);

		void setWidth(double width);
		double width();

		void setHeight(double height);
		double height();

		void setPos(const QPointF &pos);
		void setPos(qreal x, qreal y);

		void updateObject();

	private:
		double _width;
		double _height;
		QBrush _brush;
		int _border_w;
};

#endif // OBJECTTRIANGLE_H
