#include "DatePicker.h"
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>

DatePicker::DatePicker(QWidget *parent) :
	QWidget(parent)
{
	_dt = QDateTime::currentDateTime();
	_format = DATEPICKER_DEF_FORMAT;
	
	createUi();
	updateDisplay();
}

void DatePicker::createUi()
{
	_txt = new QLineEdit(this);
	_txt->setAlignment(Qt::AlignCenter);
	
	_cmdCal = new QPushButton(this);
	_cmdCal->setIcon(QIcon(":/planning/images/view-calendar.png"));
	_cmdCal->setIconSize(QSize(16, 16));
	
	_cal = new QCalendarWidget();
	_cal->setWindowModality(Qt::ApplicationModal);
	_cal->setWindowTitle("Выбор даты");
	_cal->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	_cal->hide();
	
	QHBoxLayout * mainLayout = new QHBoxLayout();
	
	mainLayout->addWidget(_txt);
	mainLayout->addWidget(_cmdCal);
	
	if (this->layout()) delete layout();
	setLayout(mainLayout);
	
	connect(_txt, SIGNAL(editingFinished()), this, SLOT(textChanged()));
	connect(_cmdCal, SIGNAL(clicked()), this, SLOT(calendarRequest()));
	connect(_cal, SIGNAL(activated(QDate)), this, SLOT(calendarDateSelected(QDate)));
}

void DatePicker::updateDisplay()
{
	_txt->setText(_dt.toString(_format));
}

void DatePicker::setDate(QDate date)
{
	_dt.setDate(date);
	updateDisplay();
	emit dateChanged(_dt);
}

void DatePicker::setTime(QTime time)
{
	_dt.setTime(time);
	updateDisplay();
	emit dateChanged(_dt);
}

QDate DatePicker::date()
{
	return _dt.date();
}

QTime DatePicker::time()
{
	return _dt.time();
}

QDateTime DatePicker::datetime()
{
	return _dt;
}

void DatePicker::setFormat(QString format)
{
	_format = format;
	updateDisplay();
}

void DatePicker::textChanged()
{
	
	QDateTime parse = QDateTime::fromString(_txt->text(), _format);
	if (parse.isValid())
	{
		_dt = parse;
		updateDisplay();
		emit dateChanged(_dt);
	}
	else
		updateDisplay();
}

void DatePicker::calendarRequest()
{
	QRect rect = _cal->geometry();
	rect.setTopLeft(QCursor::pos());
	rect.setWidth(250);
	rect.setHeight(250);
	_cal->setGeometry(rect);
	_cal->show();
}

void DatePicker::calendarDateSelected(QDate date)
{
	_cal->hide();
	setDate(date);
}



