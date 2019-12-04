#ifndef REPORTTABLEROW_H
#define REPORTTABLEROW_H

#include "ReportEngine_global.h"
#include "ReportTableColumn.h"
#include <QGraphicsRectItem>

class REPORTENGINESHARED_EXPORT ReportTableRow 
{
	public:
		ReportTableRow(int index, int columns, double top, QGraphicsRectItem *item);

		void setHeight(double value);
		void setTop(double value);
		void setWidth(double value);
		
		double height();
		double top();
		
		int columnCount();
		ReportTableColumn * column(int index);
		
	private:
		QList<ReportTableColumn *> _clmns;
		double _width;
		double _height;
		int _idx;
		double _top;
};

#endif // REPORTTABLEROW_H
