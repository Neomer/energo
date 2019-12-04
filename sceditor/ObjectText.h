#ifndef OBJECTTEXT_H
#define OBJECTTEXT_H

#include "SchemeObject.h"

#include <QGraphicsItem>
#include <QStaticText>
#include <QTextItem>
#include "../pgredrv/PgreSqlDrv.h"
#include <QTimer>
#include <QEvent>
#include <QGraphicsSceneHoverEvent>

#define OBJECT_TEXT_DEFAULT_WIDTH		60
#define OBJECT_TEXT_DEFAULT_HEIGHT		30
#define OBJECT_TEXT_DEFAULT_TEXT		QString("none")
#define OBJECT_TEXT_DEFAULT_BGCOLOR		QColor(255, 255, 255)
#define OBJECT_TEXT_DEFAULT_FORECOLOR	QColor(0, 0, 0)
#define OBJECT_SELECTION_MARKER			5


class ObjectText : public SchemeObject
{
	public:
		ObjectText(QGraphicsItem *parent = 0);
		~ObjectText();

		QRectF boundingRect() const;

		void paint(QPainter *painter,
				   const QStyleOptionGraphicsItem *option,
				   QWidget *widget);

		void setText(QString value);

		void setWidth(double width);
		double width();

		void setHeight(double height);
		double height();

		void setPos(const QPointF &pos);
		void setPos(qreal x, qreal y);

		void setAlignment(Qt::AlignmentFlag align);
		Qt::AlignmentFlag alignment();

		void setAutoResize(bool value);
		bool autoResize();

		void updateObject();

	protected:
		void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		//QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	private:
		QString _text;
		QString _source;
		double _width;
		double _height;
		Qt::AlignmentFlag _align;
		QBrush _brush;
		bool _autoresize;
		QFont _font;
		QColor _fore;
		int _border_w;
		bool _is_resize;
};

#endif // OBJECTTEXT_H
