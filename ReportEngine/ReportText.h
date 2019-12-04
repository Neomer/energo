#ifndef REPORTTEXT_H
#define REPORTTEXT_H

#include "ReportElement.h"

#include "ReportEngine_global.h"
#include <QGraphicsTextItem>
#include <QFont>

class REPORTENGINESHARED_EXPORT ReportText : public ReportElement
{
	public:

		ReportText();
		ReportText(QString text, QFont font = QFont(), Qt::AlignmentFlag alignment = Qt::AlignLeft);
		
		QGraphicsSimpleTextItem * graphicsItem();
		
		void setSize(QSize size);
		QSize size();
		
		void setText(QString text);
		QString text();
		
		void setBold(bool value);
		bool bold();
		
		void setUnderline(bool value);
		bool underline();
		
		double height();
		void setColor(QColor color);
		
	private:
		QGraphicsSimpleTextItem * _item;
		QFont _font;
};

#endif // REPORTTEXT_H
