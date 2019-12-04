#ifndef PRINTPREVIEWDLG_H
#define PRINTPREVIEWDLG_H

#include <QDialog>
#include "ReportEngine.h"

namespace Ui {
	class PrintPreviewDlg;
}

class PrintPreviewDlg : public QDialog
{
		Q_OBJECT
		
	public:
		explicit PrintPreviewDlg(ReportEngine * engine, QWidget *parent = 0);
		~PrintPreviewDlg();
		
	private:
		Ui::PrintPreviewDlg *ui;
};

#endif // PRINTPREVIEWDLG_H
