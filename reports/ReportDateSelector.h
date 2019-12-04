#ifndef REPORTDATESELECTOR_H
#define REPORTDATESELECTOR_H

#include <QDialog>
#include <QDate>
#include <QCalendarWidget>
#include <QPoint>

class ReportDateSelector : public QDialog
{
    Q_OBJECT
public:
    explicit ReportDateSelector(QWidget *parent = 0);
	~ReportDateSelector();
	void setDate(QDate date);
	static 	QPoint absolutePos(QWidget * w);

signals:
	void onDatePick(QDate date);
	
private:
	QCalendarWidget * m_cal;
	
protected slots:
	void dateSelect(QDate date);
};

#endif // REPORTDATESELECTOR_H
