#include "ObjectDataSource.h"
#include <QMessageBox>

ObjectDataSource::ObjectDataSource(QGraphicsItem *parent) :
	SchemeObject(SOT_DataSource, parent)
{

	_conn = 0;
	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(OBJECT_DATASRC_DEFAULT_BGCOLOR);
	_fore = OBJECT_DATASRC_DEFAULT_FORECOLOR;
	_border_w = 1;

	_timer = new QTimer();
	_result = 0;

	_settings << new SchemeObjectSetting("source", _source, "Ссылка на базу данных", "Database link") <<
				 new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", OBJECT_DATASRC_DEFAULT_BGCOLOR, "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("forecolor", OBJECT_DATASRC_DEFAULT_FORECOLOR, "Цвет шрифта", "Цвет текста внутри элемента") <<
				 new SchemeObjectSetting("font", _font, "Шрифт", "Формат шрифта надписи внутри элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("rotation", 0.0, "Угол поворота", "Угол поворота элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");



	_text = OBJECT_DATASRC_DEFAULT_TEXT;

	setWidth(OBJECT_DATASRC_DEFAULT_WIDTH);
	setHeight(OBJECT_DATASRC_DEFAULT_HEIGHT);
	setAlignment(Qt::AlignCenter);
	setAcceptHoverEvents(true);

	_timer->setInterval(5000);
	connect(_timer, SIGNAL(timeout()), this, SLOT(tick()));
	setEditable(true);
}

ObjectDataSource::~ObjectDataSource()
{
	delete _timer;
}

QRectF ObjectDataSource::boundingRect() const
{
	return QRectF(-0.5 * _width - _border_w * 0.5, -0.5 * _height - _border_w * 0.5,
				  _width + _border_w, _height + _border_w);
}

void ObjectDataSource::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setBrush(_brush);
	QPen border;
	if (isSelected())
		border = QPen(Qt::SolidPattern, _border_w, Qt::DashLine);
	else
		border = QPen(Qt::SolidPattern, _border_w, Qt::SolidLine);

	painter->setPen(border);

	painter->drawRect(QRect(-0.5 * _width, -0.5 * _height, _width, _height));

	painter->setPen(QPen(_fore));
	painter->setFont(_font);
	painter->drawText(boundingRect(), _align | Qt::TextWordWrap, _text);
}


void ObjectDataSource::setSource(QString data)
{
	_source = data;
	setting("source")->setValue(data);
	if (_editable)
	{
		setText(QString("ID: %1").arg(_source));
	}
}

void ObjectDataSource::setConnection(PgreSqlDrv *connection)
{
	_conn = connection;
}

void ObjectDataSource::setWidth(double width)
{
	_width = width;
	if (setting("width"))
		setting("width")->setValue(width);
	moveBy(0, 0);
	update();
}

double ObjectDataSource::width()
{
	return _width;
}

void ObjectDataSource::setHeight(double height)
{
	_height = height;
	if (setting("height"))
		setting("height")->setValue(height);
	moveBy(0, 0);
	update();
}

double ObjectDataSource::height()
{
	return _height;
}

void ObjectDataSource::setAlignment(Qt::AlignmentFlag align)
{
	_align = align;
}

Qt::AlignmentFlag ObjectDataSource::alignment()
{
	return _align;
}

void ObjectDataSource::setAutoResize(bool value)
{
	_autoresize = value;
}

bool ObjectDataSource::autoResize()
{
	return _autoresize;
}

void ObjectDataSource::setEditable(bool editable)
{
	if (editable)
	{
		_timer->stop();
		setText(QString("ID: %1").arg(_source));
	}
	else
	{
		setText(OBJECT_DATASRC_DEFAULT_TEXT);
		_timer->start();
	}
	SchemeObject::setEditable(editable);
}


void ObjectDataSource::updateObject()
{
	_brush = setting("bgcolor")->value().value<QColor>();
	_fore = setting("forecolor")->value().value<QColor>();
	_font = setting("font")->value().value<QFont>();
	_border_w = setting("border")->value().toInt();
	prepareGeometryChange();
	setPos(setting("x")->value().toDouble(), setting("y")->value().toDouble());
	setSource(setting("source")->value().toString());
	setWidth(setting("width")->value().toDouble());
	setHeight(setting("height")->value().toDouble());
	setRotation(setting("rotation")->value().toDouble());
}

void ObjectDataSource::tick()
{
	if (!_conn)
		return;

	QString sql = QString("select value, dt from data where channel=%1 and dt IN (select last_date from channel where id=%1);").arg(_source);

	if (_result)
	{
		_result->close();
		delete _result;
	}
	_result = _conn->exec(sql);

	if (!_result->isValid())
	{
		setText(OBJECT_DATASRC_DEFAULT_TEXT);
        //QMessageBox::information(0, "", _conn->getError());
	}
	else
	{
		setText(_result->getValue(0));
		setToolTip(_result->getValue(1));
	}
}

void ObjectDataSource::setText(QString text)
{
	_text = text;
	update();
}


void ObjectDataSource::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
/*	_brush.setColor(OBJECT_DATASRC_DEFAULT_BGCOLOR);
	update();*/
	QGraphicsItem::hoverLeaveEvent(event);
}


void ObjectDataSource::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
/*	_brush.setColor(QColor(190, 190, 190));
	update();*/
	QGraphicsItem::hoverEnterEvent(event);
}

/*
QVariant ObjectDataSource::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
	QPointF pos;
	switch (change)
	{
		case QGraphicsItem::ItemPositionChange:
			pos = QPointF(value.toPointF());
			//QMessageBox::information(0, "", QString("%1 x %2").arg(QString::number(pos.x()), QString::number(pos.y())));
			pos.setY(qRound((pos.y() - _height * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + _height * 0.5);
			pos.setX(qRound((pos.x() - _width * 0.5) / SCENE_GRID_SIZE) * SCENE_GRID_SIZE + _width * 0.5);
			setToolTip(QString("%1 x %2").arg(QString::number(pos.x()), QString::number(pos.y())));
			setting("x")->setValue(pos.x());
			setting("y")->setValue(pos.y());
			return QVariant::fromValue(pos);
	}
	return value;
}
*/
