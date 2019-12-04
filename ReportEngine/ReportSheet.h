#ifndef REPORTSHEET_H
#define REPORTSHEET_H

#include <QGraphicsScene>
#include "ReportEngine_global.h"
#include "ReportSheetRegion.h"

#define REPORTSHEET_DEFAULT_A4_WIDTH		760
#define REPORTSHEET_DEFAULT_A4_HEIGHT		1080

class REPORTENGINESHARED_EXPORT ReportSheet
{
	public:
		ReportSheet(QSize size);
		
		QSize size();
		int width() const;
		int height() const;
		
		void setRegionSpacing(double value);
		int regionSpacing();
		
		void addFreeElement(QPointF point, ReportElement * element);
		ReportSheetRegion * addRegion(ReportSheetRegionPosition position);
		ReportSheetRegion * region(ReportSheetRegionPosition position) const;
		
		void setMargins(ReportSheetMargins value);
		
		QGraphicsScene * scene();
		
	private:
		QList<ReportSheetRegion *> _regions;
		QSize _size;
		double _spacing;
		QGraphicsScene * _scene;
		ReportSheetMargins _margins;
};

#endif // REPORTSHEET_H
