#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <QWidget>
#include <QDateTime>
#include <QLineEdit>
#include <QPushButton>
#include <QCalendarWidget>

#define DATEPICKER_DEF_FORMAT	"yyyy-MM-dd hh:mm:ss"

class DatePicker : public QWidget
{
		Q_OBJECT
		
	public:
		explicit DatePicker(QWidget *parent = 0);
		void setDate(QDate date);
		void setTime(QTime time);
		QDate date();
		QTime time();
		QDateTime datetime();
		void setFormat(QString format);
		
	signals:
		void dateChanged(QDateTime datetime);
		
	private	slots:
		void textChanged();
		void calendarRequest();
		void calendarDateSelected(QDate date);
	
	private:
		void createUi();
		void updateDisplay();
		
		QString _format;
		QCalendarWidget * _cal;
		QDateTime _dt;
		QLineEdit * _txt;
		QPushButton * _cmdCal;
};

#endif // DATEPICKER_H
