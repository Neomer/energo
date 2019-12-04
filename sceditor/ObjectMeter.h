#ifndef OBJECTMETER_H
#define OBJECTMETER_H

#include "SchemeObject.h"
#include "../pgredrv/PgreSqlDrv.h"
#include <QTimer>

#define OBJECT_METER_DEFAULT_WIDTH	80
#define OBJECT_METER_DEFAULT_HEIGHT	80
#define OBJECT_METER_DEFAULT_TEXT		QString("none")
#define OBJECT_METER_DEFAULT_BGCOLOR	QColor(255, 255, 255)
#define OBJECT_METER_DEFAULT_FORECOLOR	QColor(0, 0, 0)


class ObjectMeter : public SchemeObject
{
		Q_OBJECT
	
	public:
		ObjectMeter(QGraphicsItem *parent = 0);
		~ObjectMeter();

		QRectF boundingRect() const;
		
        void paint(QPainter *painter, 
				   const QStyleOptionGraphicsItem *option,
                   QWidget *widget);
		
		void setSource(QString data);
		void setConnection(PgreSqlDrv * connection);

		void setWidth(double width);
		double width();

		void setHeight(double height);
		double height();

		void setAutoResize(bool value);
		bool autoResize();

		void setEditable(bool editable);

		void updateObject();

	protected:
		void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
		void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
		//QVariant itemChange(GraphicsItemChange change, const QVariant &value);

	private slots:
		void tick();

	private:
		void setText(QString text);

		PgreSqlResult * _result;
		QString _text;
		PgreSqlDrv * _conn;
		QString _source;
		double _width;
		double _height;
		Qt::AlignmentFlag _align;
		QBrush _brush;
		bool _autoresize;
		QTimer * _timer;
		QFont _font;
		QColor _fore;
		int _border_w;
		double _maxval;
};

#endif // OBJECTMETER_H
