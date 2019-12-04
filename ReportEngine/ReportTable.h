#ifndef REPORTTABLE_H
#define REPORTTABLE_H

#include "ReportElement.h"
#include "ReportEngine_global.h"
#include "ReportTableRow.h"
#include "ReportTableColumn.h"
#include "ReportTableElement.h"
#include <QTableWidget>
#include <QMap>

class REPORTENGINESHARED_EXPORT ReportTable : public ReportElement
{
	public:
		ReportTable();
		ReportTable(int rows, int columns);
		ReportTable(QTableWidget * twdgt);
		
		void addRow(ReportTableRow * row);
		void addColumn(ReportTableColumn * column);
		
		void setWidth(double width);
		void setPos(double x, double y);
		
		void setRowHeight(double value);
		void setRowHeight(int index, double value);
		
		void setColumnWidth(int index, double value);
		
		ReportTableElement * cell(int row, int column);
		ReportTableRow * row(int index);
		
		QGraphicsRectItem * graphicsItem();
		double height();
		
	private:
		QList<ReportTableRow *> _rows;
		QGraphicsRectItem * _item;
		double _width;
		double _rowheight;
		double _left;
		double _top;
};

#endif // REPORTTABLE_H
