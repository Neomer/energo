#include "ReportEngine.h"
#include <QtPlugin>
#include "PrintPreviewDlg.h"

Q_EXPORT_PLUGIN(ReportEngine);

ReportEngine::ReportEngine()
{
	_page = QSize(REPORTSHEET_DEFAULT_A4_WIDTH, REPORTSHEET_DEFAULT_A4_HEIGHT);
}

ReportEngine::~ReportEngine()
{
	foreach (ReportSheet * sheet, _sheets) 
		delete sheet;
}

bool ReportEngine::loadSource(QString filename)
{
	return true;
}

void ReportEngine::setPageSize(QSize size)
{
	_page = size;
}

void ReportEngine::appendPage(ReportSheet *page)
{
	_sheets.append(page);
}

ReportSheet *ReportEngine::appendPage()
{
	ReportSheet * sheet;
	if (_sheets.count() > 0)
		sheet = new ReportSheet(_sheets.at(0)->size());
	else
		sheet = new ReportSheet(QSize(REPORTSHEET_DEFAULT_A4_WIDTH,
									  REPORTSHEET_DEFAULT_A4_HEIGHT));
	_sheets.append(sheet);
	
	return sheet;
}

ReportSheet *ReportEngine::sheet(int index)
{
	if ((index < 0)||(index >= _sheets.count()))
	{
		qDebug("ReportEngine::sheet() - Sheet's index is out of bound!");
		return 0;
	}
	return _sheets.at(index);
}

int ReportEngine::sheetCount()
{
	return _sheets.count();
}

ReportSheet *ReportEngine::currentSheet()
{
	if (_sheets.count() == 0)
		return 0;
	return _sheets.last();
}

QFont ReportEngine::font(QString name)
{
	return _fonts.value(name, QFont());
}

void ReportEngine::registerFont(QString name, QFont font)
{
	_fonts[name] = font;
}

void ReportEngine::showPrintDialog(QWidget *parent)
{
	QPrinter printer;
	QPrintDialog prdlg(&printer, parent);
	
	if (prdlg.exec() == QDialog::Accepted)
	{
		QPainter painter;
		foreach (ReportSheet * page, _sheets)
		{
	        painter.begin(&printer);
			page->scene()->render(&painter);
			painter.end();
		}
	}
}

void ReportEngine::showPrintPreviewDialog(QWidget *parent)
{
	PrintPreviewDlg * dlg = new PrintPreviewDlg(this, parent);
	dlg->exec();
}

