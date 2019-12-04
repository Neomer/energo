#include "BalansAddSets.h"
#include "ui_BalansAddSets.h"

#include <QMessageBox>
#include <QGroupBox>

BalansAddSets::BalansAddSets(QWidget *parent, PgreSqlDrv *connection, QTreeWidgetItem *item) :
    QWidget(parent),
    ui(new Ui::BalansAddSets)
{
    ui->setupUi(this);
	this->m_connection = connection;
	this->m_node = item;
	
	updateForm();
	
	QGroupBox * gb = (QGroupBox *)parent;
	gb->setTitle(tr("Настройки организации:"));
	ui->cmdSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	
	if (parent->layout()) delete parent->layout();
	parent->setLayout(ui->mainLayout);
	
	for (int i = 0; i < this->children().count(); i++)
	{
		QWidget * w = qobject_cast<QWidget *>(this->children().at(i));
        if (w)
            if (w->objectName() != "") w->show();
	}
}

BalansAddSets::~BalansAddSets()
{
    delete ui;
}

void BalansAddSets::updateForm()
{
	PgreSqlResult * res = this->m_connection->exec(tr("select value from info where name='org_name' limit 1;"));
	
	if (!res->hasRows())
	{
		qDebug("BalansAddSets::CounterSets() - Organization name is missing\n");
	}
	else
	{
		ui->txtName->setText(res->getValue("value"));
	}
	res->close();
}

/************************************************
  
		SLOTS
		
*************************************************/
void BalansAddSets::dropChanges()
{
	updateForm();
}

void BalansAddSets::saveChanges()
{
	QMessageBox::StandardButton res = (QMessageBox::StandardButton)QMessageBox::question(this, tr("Конфигуратор"), tr("Сохранить изменения?"), QMessageBox::Yes, QMessageBox::No);
	if (res == QMessageBox::Yes)
	{
		QString sql;
		sql = "update info set value='%1' where name='org_name';";
		sql = sql.arg(ui->txtName->text());
		PgreSqlResult * r;
		if (!(r = m_connection->exec(sql))->isValid())
		{
			qDebug("BalansAddSets::saveChanges() - SQL ERROR: %s\n%s", 
			       m_connection->getError().toAscii().constData(),
			       sql.toAscii().constData());
		}
		else
		{
			m_node->setText(0, ui->txtName->text());
			emit onUpdate(m_node);
		}
	}
	updateForm();
}

void BalansAddSets::appendChild()
{
	emit onCreateChild(m_node);
}
