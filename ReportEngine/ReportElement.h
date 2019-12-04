#ifndef REPORTELEMENT_H
#define REPORTELEMENT_H

#include <QGraphicsItem>

#include "ReportEngine_global.h"

enum ReportElementType
{
	RET_Text,
	RET_Cell,
	RET_Table,
	RET_Widget
};

class REPORTENGINESHARED_EXPORT ReportElement
{
	public:
		ReportElement(ReportElementType type);
		
		ReportElementType elementType() const;
		
		void setAlignment(Qt::AlignmentFlag alignment);
		Qt::AlignmentFlag alignment();
		
		void setSize(QSize size);
		QSize size();
		
		int width();
		int height();
		
		void setColor(QColor color);
		QColor color();
		
		void setBackgroundColor(QColor color);
		QColor backgroundColor();
		
		virtual QGraphicsItem * graphicsItem() = 0;
		
	protected:
		ReportElementType _type;
		Qt::AlignmentFlag _alignment;
		QSize _size;
		QColor _color;
		QColor _bgcolor;
};

#endif // REPORTELEMENT_H
