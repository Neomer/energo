#ifndef REPORTROW_H
#define REPORTROW_H

#include <QObject>
#include <QGraphicsScene>

#include "ReportEngine_global.h"
#include "ReportText.h"
#include "ReportTable.h"
#include "ReportWidget.h"


#define REPORTROW_DEFAULT_HEIGHT	20

class ReportSheet;

class REPORTENGINESHARED_EXPORT ReportSheetMargins
{
	public:
		ReportSheetMargins(int l, int r, int t, int b)
		{
			_left = l;
			_right = r;
			_top = t;
			_bottom = b;
		}
		
		ReportSheetMargins()
		{
			_left = 10;
			_right = 10;
			_top = 10;
			_bottom = 10;
		}
		
		int vertical() { return _top + _bottom; }
		int horizontal() { return _left + _right; }
		int top() { return _top; }
		int bottom() {return _bottom; }
		int left() { return _left; }
		int right() { return _right; }
		
	private:
		int _left;
		int _right;
		int _top;
		int _bottom;
};

class REPORTENGINESHARED_EXPORT ReportRow
{

	public:
		ReportRow(QGraphicsScene * scene, double top, double height, ReportSheetMargins *margins);
		
		double top();
		double height();
		
		void addText(QString text);
		void addText(QString text, QFont font);
		void addText(ReportText * item);
		
		void addTable(ReportTable * item);
		void addWidget(ReportWidget * widget);
		
		
	private:
		QList<ReportElement *> _elements;
		QGraphicsScene * _scene;
		double _top;
		double _width;
		double _height;
		ReportSheetMargins * _margins;
};

#endif // REPORTROW_H
