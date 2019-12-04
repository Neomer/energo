#include "ReportTableColumn.h"

ReportTableColumn::ReportTableColumn(int width)
{
	_width = width;
}

void ReportTableColumn::setElement(ReportTableElement *element)
{
	_elem = element;
}

ReportTableElement *ReportTableColumn::element()
{
	return _elem;
}

