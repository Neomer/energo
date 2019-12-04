#include "UserSets.h"
#include "ui_UserSets.h"
#include <QMessageBox>

UserSets::UserSets(QWidget *parent, PgreSqlDrv *connection, int id, QTreeWidgetItem *item) :
	QWidget(parent),
	ui(new Ui::UserSets)
{
	ui->setupUi(this);
	_conn = connection;
	
	PgreSqlResult * r = _conn->exec(QString("select * from users where id=%1;").arg(QString::number(id)));
	if (r->isValid())
	{
		if (r->hasRows())
		{
			ui->txtName->setText(r->getValue("name"));
			ui->txtLogin->setText(r->getValue("login"));
		}
		else
		{
			QMessageBox::critical(parent, tr("Конфигуратор"), tr("Пользователь не найден!"));
			return;
		}
	}
	else
	{
		qDebug("UserSets::UserSets() - SQL ERROR: %s",
			   _conn->getError().toAscii().constData());

		QMessageBox::critical(parent, tr("Конфигуратор"), tr("Невозможно выполнить запрос к БД!"));
		return;
	}
			
	r = _conn->exec("select * from factory order by name;");
	if (r->isValid())
	{
		while (r->notEoF())
		{
			QTreeWidgetItem * twi = new QTreeWidgetItem();
			twi->setText(0, r->getValue("name"));
			twi->setIcon(0, QIcon(":/icons/images/server.png"));
			twi->setCheckState(0, Qt::Checked);
			
			for (int i = 0; i < ui->twAccess->topLevelItemCount(); i++)
			{
				QTreeWidgetItem * root = ui->twAccess->topLevelItem(i);
				
				root->addChild(twi->clone());
			}
			delete twi;
			
			r->moveNext();
		}
		connect(ui->twAccess, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(itemChanged(QTreeWidgetItem*,int)));
	}
	else
	{
		qDebug("UserSets::UserSets() - SQL ERROR: %s",
			   _conn->getError().toAscii().constData());

		QMessageBox::critical(parent, tr("Конфигуратор"), tr("Невозможно выполнить запрос к БД!"));
		return;
	}
	
}

UserSets::~UserSets()
{
	delete ui;
}

void UserSets::itemChanged(QTreeWidgetItem *item, int column)
{
	for (int i = 0; i < item->childCount(); i++)
	{
		item->child(i)->setCheckState(0, item->checkState(0));
	}
	if (item->parent() != 0)
	{
		bool full = false;
		for (int i = 0; i < item->parent()->childCount(); i++)
		{
			full |= item->parent()->child(i)->checkState(0) != item->checkState(0);
		}
		if (full)
		{
			item->parent()->setCheckState(0, item->checkState(0));
		}
		else
		{
			item->parent()->setCheckState(0, Qt::PartiallyChecked);
		}
	}
}
