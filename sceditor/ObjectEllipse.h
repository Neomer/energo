#ifndef OBJECTELLIPSE_H
#define OBJECTELLIPSE_H

#include "SchemeObject.h"

#include <QObject>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>

#define OBJECT_ELLIPSE_DEFAULT_WIDTH		60
#define OBJECT_ELLIPSE_DEFAULT_HEIGHT		30
#define OBJECT_ELLIPSE_DEFAULT_BGCOLOR		QColor(255, 255, 255)
#define OBJECT_SELECTION_MARKER			5


class ObjectEllipse : public SchemeObject
{
	public:
		ObjectEllipse(QGraphicsItem *parent = 0);
		~ObjectEllipse();

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

	protected:
		//void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
		//void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		//QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	private:
		double _width;
		double _height;
		QBrush _brush;
		int _border_w;
		bool _is_resize;
};

#endif // OBJECTELLIPSE_H
