#include "transformerexchange.h"
#include "ui_transformerexchange.h"
#include <QFileDialog>

TransformerExchange::TransformerExchange(QWidget *parent, PgreSqlDrv *connection, int id) :
    QDialog(parent),
    ui(new Ui::TransformerExchange)
{
    ui->setupUi(this);
	m_db = connection;
    m_id = id;
	
    if (this->layout()) delete this->layout();
	this->setLayout(ui->mainlLayout);
    
    connect(ui->cmdAddImage, SIGNAL(clicked(bool)), this, SLOT(addFile()));
}

TransformerExchange::~TransformerExchange()
{
    delete ui;
}

void TransformerExchange::accept()
{
    if (m_file != "")
    {
        
    }
    
    QDialog::accept();
}

void TransformerExchange::addFile()
{
    m_file = QFileDialog::getOpenFileName(this, QString() ,QString() , tr("װאיכû (*.png *.jpg *.pdf)"));
    if (m_file == "")
        return;
}
