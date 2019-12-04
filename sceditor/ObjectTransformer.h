#ifndef OBJECTTRANSFORMER_H
#define OBJECTTRANSFORMER_H

#include <QGraphicsItem>
#include <QPainter>

class ObjectTransformer : public QGraphicsItem
{
		
	public:
		ObjectTransformer(QGraphicsItem * parent = 0);
		QRectF boundingRect() const;
		
        void paint(QPainter *painter, 
				   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);
		
	private:
		
};

#endif // OBJECTTRANSFORMER_H
