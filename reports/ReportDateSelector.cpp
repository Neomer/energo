#include "ReportDateSelector.h"
#include <QGridLayout>
#include <QGraphicsAnchorLayout>
#include <QRect>

ReportDateSelector::ReportDateSelector(QWidget *parent) :
    QDialog(parent)
{
	m_cal = new QCalendarWidget(this);
	if (parent)	
	{
		QPoint pos = absolutePos(parent);
		pos += QPoint(0, parent->height());
		QRect rect(pos, QPoint(0, 0));
		this->setGeometry(rect);
	}
	QGridLayout * mainLayout = new QGridLayout();
	mainLayout->addWidget(m_cal, 0, 0);
	this->setLayout(mainLayout);
	this->setWindowTitle(tr("Выбор даты"));
	this->setAttribute(Qt::WA_DeleteOnClose);
	connect(m_cal, SIGNAL(activated(QDate)), this, SLOT(dateSelect(QDate)));
}

ReportDateSelector::~ReportDateSelector()
{
	if (m_cal) delete m_cal;
}

void ReportDateSelector::setDate(QDate date)
{
	if (date.isValid()) m_cal->setSelectedDate(date);
}

void ReportDateSelector::dateSelect(QDate date)
{
	emit onDatePick(date);
	this->close();
}

QPoint ReportDateSelector::absolutePos(QWidget *w)
{
	QPoint ret(w->x(), w->y());
	if (w->parent()) ret += absolutePos((QWidget *)w->parent());
	return ret;
}
