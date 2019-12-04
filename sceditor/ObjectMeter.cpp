#include "ObjectMeter.h"
#include <math.h>
#include <QStaticText>

#define PI		3.141592653589

ObjectMeter::ObjectMeter(QGraphicsItem *parent) :
	SchemeObject(SOT_Meter, parent)
{
	_conn = 0;
	_brush.setStyle(Qt::SolidPattern);
	_brush.setColor(OBJECT_METER_DEFAULT_BGCOLOR);
	_fore = OBJECT_METER_DEFAULT_FORECOLOR;
	_border_w = 1;
	_maxval = 1000;

	_timer = new QTimer();
	_result = 0;
	_text = OBJECT_METER_DEFAULT_TEXT;

	_settings << new SchemeObjectSetting("source", _source, "Ссылка на базу данных", "Ссылка на базу данных") <<
				 new SchemeObjectSetting("legend", _text, "Подпись", "Обозначение в нижней части элемента") <<
				 new SchemeObjectSetting("maxvalue", _maxval, "Максимальное значение", "Правая граница шкалы") <<
				 new SchemeObjectSetting("width", _width, "Ширина", "Ширина элемента в пикселах") <<
				 new SchemeObjectSetting("height", _height, "Высота", "Высота элемента в пикселах") <<
				 new SchemeObjectSetting("bgcolor", OBJECT_METER_DEFAULT_BGCOLOR, "Заливка", "Фоновый цвет элемента") <<
				 new SchemeObjectSetting("forecolor", OBJECT_METER_DEFAULT_FORECOLOR, "Цвет шрифта", "Цвет текста внутри элемента") <<
				 new SchemeObjectSetting("font", _font, "Шрифт", "Формат шрифта надписи внутри элемента") <<
				 new SchemeObjectSetting("border", _border_w, "Толщина границы", "Толщина линии границ элемента") <<
				 new SchemeObjectSetting("rotation", 0.0, "Угол поворота", "Угол поворота элемента") <<
				 new SchemeObjectSetting("x", pos().x(), "X", "Смещение элемента от левой границы окна") <<
				 new SchemeObjectSetting("y", pos().y(), "Y", "Смещение элемента от верхней границы окна");




	setWidth(OBJECT_METER_DEFAULT_WIDTH);
	setHeight(OBJECT_METER_DEFAULT_HEIGHT);
//	setAcceptHoverEvents(true);

	_align = Qt::AlignCenter;
	
	_timer->setInterval(5000);
	connect(_timer, SIGNAL(timeout()), this, SLOT(tick()));
	setEditable(true);
	
}

ObjectMeter::~ObjectMeter()
{
	delete _timer;
}

QRectF ObjectMeter::boundingRect() const
{
	return QRectF(-0.5 * _width * _detalization - _border_w * 0.5, -0.5 * _height * _detalization - _border_w * 0.5,
				  _width * _detalization + _border_w, _height * _detalization + _border_w);
}

void ObjectMeter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	double fact_width = _width * _detalization,
			fact_height = _height * _detalization;
	
/*	if ((fact_width < 10) || (fact_height < 10))
	{
		setEditable(false);
		return;
	}
	else
	{
		setEditable(true);
	}
*/
	painter->setBrush(_brush);
	QPen border;
	if (isSelected())
		border = QPen(Qt::SolidPattern, _border_w, Qt::DashLine);
	else
		border = QPen(Qt::SolidPattern, _border_w, Qt::SolidLine);

	painter->setPen(border);

	painter->drawRect(QRect(
						  -0.5 * fact_width, 
						  -0.5 * fact_height, 
						  fact_width, 
						  fact_height));

	double val;
	if (_result)
	{
		val = _result->getValue(0).toDouble();
		val = qMin(val, _maxval);
	}
	else
		val = 0;
	
	painter->drawLine(QPointF(-0.5 * fact_width, 0.2 * fact_height),
					  QPointF(0.5 * fact_width, 0.2 * fact_height));
	
	QRect txtrect = QFontMetrics(_font).boundingRect(_text);
	if ((txtrect.width() < fact_width)&&(txtrect.height() < fact_height))
	{
		
		painter->setPen(QPen(_fore));
		painter->setFont(_font);
		painter->drawText(QRectF(QPointF(-0.5 * fact_width, 0.25 * fact_height), 
								 QSize(fact_width, 0.25 * fact_height)), _align | Qt::TextWordWrap, _text);
	}
	
	// Рисуем стрелку и сетку
	double radius = qMin(0.8 * fact_height, 0.5 * fact_width),
			angle = 2 * PI - (val / _maxval * PI + PI * 0.5);
	
	QPointF startp(0, 0.2 * fact_height);
	QPointF endp(radius * sin(angle), radius * cos(angle));
	endp += startp;

	if (_detalization >= 0.2)
	{
		painter->setPen(QPen(Qt::SolidPattern, 1, Qt::DotLine));
		painter->drawArc(QRectF(-0.8 * radius, 0.2 * fact_height - 0.8 * radius, 1.6 * radius, 1.6 * radius), 0, 2880);
	}
	
	painter->setPen(QPen(Qt::SolidPattern, 2, Qt::SolidLine));
	painter->drawLine(startp,
					  endp);
	
}

void ObjectMeter::setSource(QString data)
{
	_source = data;
	setting("source")->setValue(data);
}

void ObjectMeter::setConnection(PgreSqlDrv *connection)
{
	_conn = connection;
}



void ObjectMeter::tick()
{
	if (!_conn)
		return;

	QString sql = QString("select value, dt from data where channel=%1 and dt IN (select last_date from channel where id=%1);").arg(_source);

	if (_result)
	{
		_result->close();
		delete _result;
		_result = 0;
	}
	_result = _conn->exec(sql);

	if (!_result->isValid())
	{
		_result->close();
		delete _result;
		_result = 0;
	}
	else
	{
		setToolTip(_result->getValue(1));
		update();
	}
}

void ObjectMeter::setText(QString text)
{
	_text = text;
	update();
}

void ObjectMeter::setEditable(bool editable)
{
	if (editable)
	{
		_timer->stop();
	}
	else
	{
		_timer->start();
	}
	SchemeObject::setEditable(editable);
}

void ObjectMeter::updateObject()
{
	_brush = setting("bgcolor")->value().value<QColor>();
	_fore = setting("forecolor")->value().value<QColor>();
	_font = setting("font")->value().value<QFont>();
	_border_w = setting("border")->value().toInt();
	_maxval = setting("maxvalue")->value().toDouble();
	prepareGeometryChange();
	setPos(setting("x")->value().toDouble(), setting("y")->value().toDouble());
	setSource(setting("source")->value().toString());
	setWidth(setting("width")->value().toDouble());
	setHeight(setting("height")->value().toDouble());
	setText(setting("legend")->value().toString());
	setRotation(setting("rotation")->value().toDouble());
	update();
}

void ObjectMeter::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
}

void ObjectMeter::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
}


void ObjectMeter::setWidth(double width)
{
	_width = width;
	if (setting("width"))
		setting("width")->setValue(width);
	moveBy(0, 0);
	update();
}

double ObjectMeter::width()
{
	return _width;
}

void ObjectMeter::setHeight(double height)
{
	_height = height;
	if (setting("height"))
		setting("height")->setValue(height);
	moveBy(0, 0);
	update();
}


double ObjectMeter::height()
{
	return _height;
}
