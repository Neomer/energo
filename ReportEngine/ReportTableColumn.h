#ifndef REPORTTABLECOLUMN_H
#define REPORTTABLECOLUMN_H

#include "ReportElement.h"
#include "ReportTableElement.h"
#include "ReportEngine_global.h"

class REPORTENGINESHARED_EXPORT ReportTableColumn
{
	public:
		ReportTableColumn(int width);
		
		void setElement(ReportTableElement * element);
		ReportTableElement * element();
		
	private:
		ReportTableElement * _elem;
		int _width;
};

#endif // REPORTTABLECOLUMN_H
