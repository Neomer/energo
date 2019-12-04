#include "PrintPreviewDlg.h"
#include "ui_PrintPreviewDlg.h"

PrintPreviewDlg::PrintPreviewDlg(ReportEngine *engine, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PrintPreviewDlg)
{
	ui->setupUi(this);
	
	if (layout()) delete layout();
	setLayout(ui->mainLayout);
	
	ui->gv->setScene(engine->sheet(0)->scene());
}

PrintPreviewDlg::~PrintPreviewDlg()
{
	delete ui;
}
