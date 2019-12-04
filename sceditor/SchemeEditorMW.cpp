#include "SchemeEditorMW.h"
#include "ui_SchemeEditorMW.h"
#include <QMenu>
#include <QGraphicsItem>
#include <QMessagebox>
#include <QScrollBar>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>

#include "ObjectTransformer.h"
#include "ObjectDataSource.h"
#include "ObjectText.h"
#include "ObjectRect.h"
#include "ObjectEllipse.h"
#include "ObjectLine.h"

SchemeEditorMW::SchemeEditorMW(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::SchemeEditorMW)
{
	ui->setupUi(this);
	
	if (ui->centralWidget->layout()) delete ui->centralWidget->layout();
	ui->centralWidget->setLayout(ui->mainLayout);

	_scene = new SchemeScene(QRectF(0, 0, 1000, 1000));
	
	connect(_scene, SIGNAL(selectionChanged()),
			this, SLOT(test()));

	connect(ui->twSettings, SIGNAL(itemSelectionChanged()), this, SLOT(settingItemChanged()));
	connect(ui->twSettings, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(settingEdited(QTableWidgetItem*)));

	createToolBox();

	drv = new PgreSqlDrv();
	drv->connect("192.168.80.210", "energo_sys", "energo_sys_pwd", "energo", true);
	
	ui->graphicsView->setMouseTracking(true);
	ui->graphicsView->setScene(_scene);

	ui->graphicsView->verticalScrollBar()->setValue(ui->graphicsView->verticalScrollBar()->minimum());
	ui->graphicsView->horizontalScrollBar()->setValue(ui->graphicsView->horizontalScrollBar()->minimum());
	
	setWindowState(Qt::WindowMaximized);
	stateSwap();
}

SchemeEditorMW::~SchemeEditorMW()
{
	delete ui;
}

void SchemeEditorMW::test()
{
	if (_scene->selectedItems().count() == 0)
	{
		return;
	}
	SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(0));
	if (!so)
		return;

	ObjectDataSource * ds;
	QList<SchemeObjectSetting *> set;

	ui->twSettings->clear();
	ui->twSettings->setHorizontalHeaderLabels(QStringList() << tr("Наименование") << tr("Значение"));

	set = so->settings();

	ui->twSettings->setRowCount(set.count());
	for (int i = 0; i < set.count(); i++)
	{
		QTableWidgetItem * twi = new QTableWidgetItem();
		twi->setText(tr(set.at(i)->description().toAscii().constData()));
		twi->setData(Qt::UserRole, (int)set.at(i));
		twi->setFlags(Qt::ItemIsEnabled);
		ui->twSettings->setItem(i, 0, twi);
		twi = new QTableWidgetItem();
		switch (set.at(i)->value().type())
		{
			case QVariant::String:
				twi->setText(set.at(i)->value().toString());
				break;

			case QVariant::Double:
				twi->setText(QString::number(set.at(i)->value().toDouble(), 'f', 3));
				break;

			case QVariant::Int:
				twi->setText(QString::number(set.at(i)->value().toInt()));
				break;

			case QVariant::Color:
				twi->setBackgroundColor(set.at(i)->value().value<QColor>());
				twi->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				break;

			case QVariant::Font:
				twi->setText(set.at(i)->value().value<QFont>().toString());
				break;
		}

		twi->setData(Qt::UserRole, (int)set.at(i));
		ui->twSettings->setItem(i, 1, twi);
	}
}

void SchemeEditorMW::addDbLink()
{
	ObjectDataSource * item = _scene->addDataSource();
	item->setConnection(drv);
	item->setSource("511");
}

void SchemeEditorMW::addTextObject()
{
	_scene->addText();
}

void SchemeEditorMW::addRectObject()
{
	_scene->addRect();
}

void SchemeEditorMW::addEllipseObject()
{
	_scene->addEllipse();
}

void SchemeEditorMW::addLineObject()
{
	ObjectLine * item = new ObjectLine();
	_scene->addItem(item);
}

void SchemeEditorMW::addTriangle()
{
	_scene->addTriangle();
}

void SchemeEditorMW::addMeter()
{
	ObjectMeter * item = _scene->addMeter();
	item->setConnection(drv);
	item->setSource("511");
}

void SchemeEditorMW::addConnectionLine()
{
	if (_scene->selectedItems().count() != 2)
	{
		QMessageBox::critical(this, tr("Ошибка создания связи"), tr("Необходимо выделить ровно 2 объекта!"));
		return;
	}
	SchemeObject * so1 = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(0)),
				 * so2 = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(1));

	_scene->connectObjects(so1, so2);
}

void SchemeEditorMW::settingItemChanged()
{
	if (ui->twSettings->selectedItems().count() == 0)
		return;

	SchemeObjectSetting * set = (SchemeObjectSetting *)ui->twSettings->selectedItems().at(0)->data(Qt::UserRole).toInt();
	ui->lblHelp->setText(tr(set->help().toAscii().constData()));
	switch (set->value().type())
	{
		case QVariant::Color:
			colorPickerRequest(ui->twSettings->selectedItems().at(0));
			break;

		case QVariant::Font:
			fontPickerRequest(ui->twSettings->selectedItems().at(0));
			break;
	}
}

void SchemeEditorMW::settingEdited(QTableWidgetItem *item)
{
	if (item->column() == 0)
		return;

	SchemeObjectSetting * set = (SchemeObjectSetting *)item->data(Qt::UserRole).toInt();

	bool ok = true;
	QVariant old = set->value();

	switch (set->value().type())
	{
		case QVariant::String:
			set->setValue(item->text());
			break;

		case QVariant::Double:
			set->setValue(item->text().toDouble(&ok));
			break;

		case QVariant::Int:
			set->setValue(item->text().toInt(&ok));
			break;

		case QVariant::Color:
			break;

		case QVariant::Font:
			break;
	}
	if (!ok)
	{
		QMessageBox::critical(this, tr("Ошибка формата данных"), tr("Неверный формат введенных данных!"));
		set->setValue(old);
		item->setText(old.toString());
	}
	else
	{
		SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(0));
		so->updateObject();
	}
}

void SchemeEditorMW::stateSwap()
{
	for (int i = 0; i < _scene->items().count(); i++)
	{
		SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->items().at(i));
		so->setEditable(ui->actEditState->isChecked());
	}
	for (int i = 0; i < ui->layoutSettings->count(); i++)
	{
		if (ui->layoutSettings->itemAt(i)->widget())
			ui->layoutSettings->itemAt(i)->widget()->setVisible(ui->actEditState->isChecked());
	}
	ui->actDbLink->setEnabled(ui->actEditState->isChecked());
	ui->actTextObject->setEnabled(ui->actEditState->isChecked());
	ui->actRect->setEnabled(ui->actEditState->isChecked());
	ui->actEllipse->setEnabled(ui->actEditState->isChecked());
	ui->actTriangle->setEnabled(ui->actEditState->isChecked());
	ui->actConnectionLine->setEnabled(ui->actEditState->isChecked());
	ui->actBreaker->setEnabled(ui->actEditState->isChecked());
	ui->actOilBreaker->setEnabled(ui->actEditState->isChecked());
	ui->actLine->setEnabled(ui->actEditState->isChecked());
}

void SchemeEditorMW::saveSchema()
{
	if (!_file.isOpen())
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить как..."), qApp->applicationDirPath(), tr("Файл схемы (*.esch)"));
/*		if (!QFile::exists(filename))
			return;
*/
		if (filename == "")
			return;
		_file.setFileName(filename);
		if (!_file.open(QIODevice::ReadWrite))
		{
			QMessageBox::critical(this, tr("Ошибка доступа"), tr("Невозможно получить доступ к файлу!\nВозможно он занят другим процессом."));
			return;
		}
	}
	else
	{
		_file.resize(0);
	}
	for (int i = 0; i < _scene->items().count(); i++)
	{
		SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->items().at(i));
		_file.write("ITEM=");
		_file.write(QString::number((int)so->objType()).toAscii().constData());
		_file.write("\n");
		QList<SchemeObjectSetting *> sets = so->settings();
		for (int s = 0; s < sets.count(); s++)
		{
			_file.write(sets.at(s)->name().toAscii().constData());
			_file.write("=");
			_file.write(QTextCodec::codecForName("windows-1251")->fromUnicode(sets.at(s)->value().toString()).constData());
			_file.write("\n");
		}
		_file.write("ENDITEM\n");
	}
}


void SchemeEditorMW::openSchema()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Открыть..."), qApp->applicationDirPath(), tr("Файл схемы (*.esch)"));

	if (filename == "")
		return;

	_file.setFileName(filename);
	if (!_file.open(QIODevice::ReadWrite))
	{
		QMessageBox::critical(this, tr("Ошибка доступа"), tr("Невозможно получить доступ к файлу!\nВозможно он занят другим процессом."));
		return;
	}
	while (!_file.atEnd())
	{
		QString line(_file.readLine());
		QStringList lp = line.split('=');
		if (lp.count() == 2)
		{
			if (lp.at(0) == "ITEM")
			{
				ObjectText * ot;
				ObjectDataSource * ods;
				ObjectRect * orc;
				ObjectEllipse * ol;
				ObjectMeter * om;

				SchemeObject * so;
				switch ((SchemeObjectType)lp.at(1).toInt())
				{
					case SOT_Text:
						ot = new ObjectText();
						so = (SchemeObject *)ot;
						break;

					case SOT_DataSource:
						ods = new ObjectDataSource();
						ods->setConnection(drv);
						so = (SchemeObject *) ods;
						break;

					case SOT_Rect:
						orc = new ObjectRect();
						so = (SchemeObject *)orc;
						break;

					case SOT_Ellipse:
						ol = new ObjectEllipse();
						so = (SchemeObject *)ol;
						break;
						
					case SOT_Meter:
						om = new ObjectMeter();
						so = (SchemeObject *)om;
						break;
				}
				bool enditem = false;
				while ((!_file.atEnd())&&(!enditem))
				{
					QString line(_file.readLine());
					line = line.left(line.length() - 1);
					QStringList lp = line.split('=');
					if (lp.count() == 2)
					{
						switch (so->setting(lp.at(0))->value().type())
						{
							case QVariant::Color:
								so->setting(lp.at(0))->setValue(QVariant::fromValue(QColor(lp.at(1))));
								break;

							case QVariant::Font:
								so->setting(lp.at(0))->setValue(QVariant::fromValue(QFont(lp.at(1))));
								break;

							case QVariant::String:
								so->setting(lp.at(0))->setValue(QVariant::fromValue(tr(lp.at(1).toAscii().constData())));
								break;

							case QVariant::Double:
								so->setting(lp.at(0))->setValue(QVariant::fromValue(lp.at(1).toDouble()));
								break;

							case QVariant::Int:
								so->setting(lp.at(0))->setValue(QVariant::fromValue(lp.at(1).toInt()));
								break;
						}
					}
					else
					{
						if (lp.at(0) == "ENDITEM")
						{
							enditem = true;
						}
					}
				}
				_scene->addItem(so);
				so->updateObject();

			}
		}
	}
	stateSwap();
}

void SchemeEditorMW::colorPickerRequest(QTableWidgetItem *item)
{
	item->setSelected(false);
	SchemeObjectSetting * set = (SchemeObjectSetting *)item->data(Qt::UserRole).toInt();

	QColorDialog * dlg = new QColorDialog(set->value().value<QColor>(), this);
	dlg->setOption(QColorDialog::ShowAlphaChannel);
	dlg->exec();
	if (dlg->result() == QDialog::Accepted)
	{
		set->setValue(dlg->selectedColor());
		item->setBackgroundColor(dlg->selectedColor());
		SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(0));
		so->updateObject();

	}
	delete dlg;
}

void SchemeEditorMW::fontPickerRequest(QTableWidgetItem *item)
{
	item->setSelected(false);
	SchemeObjectSetting * set = (SchemeObjectSetting *)item->data(Qt::UserRole).toInt();

	QFontDialog * dlg = new QFontDialog(set->value().value<QFont>(), this);
	dlg->exec();
	if (dlg->result() == QDialog::Accepted)
	{
		set->setValue(dlg->selectedFont());
		item->setText(dlg->selectedFont().toString());
		SchemeObject * so = qgraphicsitem_cast<SchemeObject *>(_scene->selectedItems().at(0));
		so->updateObject();

	}
	delete dlg;
}

void SchemeEditorMW::createToolBox()
{
	connect(ui->actOpen, SIGNAL(triggered()), this, SLOT(openSchema()));
	connect(ui->actSave, SIGNAL(triggered()), this, SLOT(saveSchema()));

	connect(ui->actDbLink, SIGNAL(triggered()), this, SLOT(addDbLink()));
	connect(ui->actTextObject, SIGNAL(triggered()), this, SLOT(addTextObject()));
	connect(ui->actEditState, SIGNAL(triggered()), this, SLOT(stateSwap()));
	connect(ui->actRect, SIGNAL(triggered()), this, SLOT(addRectObject()));
	connect(ui->actEllipse, SIGNAL(triggered()), this, SLOT(addEllipseObject()));
	connect(ui->actConnectionLine, SIGNAL(triggered()), this, SLOT(addConnectionLine()));
	connect(ui->actLine, SIGNAL(triggered()), this, SLOT(addLineObject()));
	connect(ui->actTriangle, SIGNAL(triggered()), this, SLOT(addTriangle()));
	connect(ui->actMeter, SIGNAL(triggered()), this, SLOT(addMeter()));
}
