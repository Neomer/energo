#ifndef TRANSFORMEREXCHANGE_H
#define TRANSFORMEREXCHANGE_H

#include <QDialog>
#include "../pgredrv/PgreSqlDrv.h"
#include <QFile>

namespace Ui {
class TransformerExchange;
}

class TransformerExchange : public QDialog
{
    Q_OBJECT
    
public:
    explicit TransformerExchange(QWidget *parent, PgreSqlDrv *connection, int id);
    ~TransformerExchange();
    
private slots:
    void accept();
    void addFile();
    
private:
    Ui::TransformerExchange *ui;
    PgreSqlDrv * m_db;
    int m_id;
    QString m_file;
};

#endif // TRANSFORMEREXCHANGE_H
