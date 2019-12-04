#include "ObjectTransformer.h"
#include <QStaticText>

ObjectTransformer::ObjectTransformer(QGraphicsItem *parent) :
	QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);
}

QRectF ObjectTransformer::boundingRect() const
{
	qreal penWidth = 1;
	return QRectF(-10 - penWidth / 2, -15 - penWidth / 2,
				  20 + penWidth, 30 + penWidth);
}

void ObjectTransformer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawEllipse(QPoint(0, -5), 10, 10);
	painter->drawEllipse(QPoint(0, 5), 10, 10);
}
