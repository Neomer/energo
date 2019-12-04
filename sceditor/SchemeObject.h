#ifndef SCHEMEOBJECT_H
#define SCHEMEOBJECT_H

#include <QString>
#include <QList>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QIcon>
#include <QMap>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>

#include "SchemeObjectSetting.h"

class ObjectConnectionLine;

//#include "AbstractObjectConnectionLine.h"

#define SCENE_GRID_SIZE			1
#define OBJECT_ZVALUE_DIFF		0.001

enum SchemeObjectType
{
	SOT_DataSource = 0,
	SOT_Text = 1,
	SOT_Rect = 2,
	SOT_Ellipse = 3,
	SOT_Triangle = 4,
	SOT_Line = 5,
	SOT_Meter = 6,
	SOT_ConnectionLine = 100
};

enum SchemeObjectResizeDirection
{
	RD_LeftTop,
	RD_LeftBottom,
	RD_RightTop,
	RD_RightBottom
};

class SchemeObject : public QObject, public QGraphicsItem

{
	Q_OBJECT

	public:
		SchemeObject(SchemeObjectType type, QGraphicsItem *parent = 0);
		~SchemeObject();
		
		QString objectName();
		void setObjectName(QString name);
		
		QPoint position();
		void setPosition(QPoint point);
		
		QSize size();
		void setSize(QSize size);
		
		QPoint absolutePosition();
		
		SchemeObject * parent();
		
		QPixmap pixmap();

		SchemeObjectSetting * setting(QString name);
		QList<SchemeObjectSetting *> settings();
		void setSettings(QList<SchemeObjectSetting *> settings);

		SchemeObjectType objType() const;

		void setConnectionLine(SchemeObject *line);
		ObjectConnectionLine * connectionLine();
		void connectWith(SchemeObject * object, SchemeObject *connector);
		void removeConnectionLine(SchemeObject * line);

		virtual void updateObject() = 0;

		virtual void setWidth(double width) = 0;
		virtual double width() = 0;
		virtual void setHeight(double height) = 0;
		virtual double height() = 0;

		virtual void setEditable(bool editable);
		virtual bool editable();
		
		virtual void setDetalization(double value);
		double detalization();

	private:
		void updateConnectionLine(QPointF point);

	private slots:
		void bringToFront();
		void sendToBack();
		void copy();
		void remove();

	signals:
		void copied();
		
	protected:

		void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
		QVariant itemChange(GraphicsItemChange change, const QVariant &value);

		void appendChild(SchemeObject * child);

		QString _name;
		QPoint _position;
		QSize _size;
		bool _operable;
		QPixmap _pixmap;
		SchemeObject * _parent;
		QList<SchemeObject *> _children;
		QList<SchemeObjectSetting *> _settings;
		SchemeObjectType _type;
		SchemeObjectResizeDirection _rd;
		QList<SchemeObject *> _connline;
		QMenu * _menu;
		bool _editable;
		double _detalization;
};

#endif // SCHEMEOBJECT_H
