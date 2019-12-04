#ifndef REPORTSHEETHEADER_H
#define REPORTSHEETHEADER_H

#include "ReportEngine_global.h"

#include <QList>
#include <QGraphicsScene>

#include "ReportRow.h"

class ReportSheet;

enum ReportSheetRegionPosition
{
	RegionTop,
	RegionMiddle,
	RegionBottom
};

class REPORTENGINESHARED_EXPORT ReportSheetRegion
{
	public:
		ReportSheetRegion(ReportSheetRegionPosition position, QSize size, double top, QGraphicsScene * scene);
		
		QSize size();
		double width() const;
		double height() const;
		double top() const;
		
		
		void setLineHeight(int value);
		int lineHeight();
		
		void setLineSpacing(int value);
		int lineSpacing();
		
		ReportRow * appendRow();
		void appendRow(ReportRow * row);
		
		ReportRow * row(int index);
		
		void setMargins(ReportSheetMargins value);
		
		ReportSheetRegionPosition position();
		
	private:
		void move(double top);
		void setHeight(double value);

		QSize _size;
		QList <ReportRow *> _rows;
		int _spacing;
		int _rowheight;
		ReportSheetMargins _margins;
		QGraphicsScene * _scene;
		double _top;
		ReportRow * currentRow();
		ReportSheetRegionPosition _pos;
		
	friend class ReportSheet;
};

#endif // REPORTSHEETHEADER_H
