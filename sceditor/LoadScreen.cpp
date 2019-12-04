#include "LoadScreen.h"
#include "ui_LoadScreen.h"

LoadScreen::LoadScreen(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LoadScreen)
{
	ui->setupUi(this);

	delete layout();
	setLayout(ui->mainLayout);
	QGraphicsScene * scene = new QGraphicsScene(QRectF(0, 0, 128, 128));

	scene->addPixmap(QIcon(":/sceditor/toolbox/objects/katomic-3.png").pixmap(QSize(128, 128)));
	ui->gv->setScene(scene);
}

LoadScreen::~LoadScreen()
{
	delete ui;
}
