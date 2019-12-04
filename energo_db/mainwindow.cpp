#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../pgredrv/PgreSqlDrv.h"
#include <QRegExpValidator>
#include <QRegExp>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    if (ui->centralWidget->layout()) 
        delete ui->centralWidget->layout();

    ui->centralWidget->setLayout(ui->mainLayout);
    
    createSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionAbout()
{
    
}

void MainWindow::commandInstall()
{
    PgreSqlDrv * conn = new PgreSqlDrv();
    
    QRegExp ip_reg("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    if (!ip_reg.exactMatch(ui->txtIP->text()))
    {
        addLog(tr("Неверный формат IP-адреса!"));
        return;
    }
    
    if (!conn->connect(ui->txtIP->text(), ui->txtLogin->text(), ui->txtPassword->text(), ui->txtDB->text()))
    {
        addLog(tr("Невозможно подключиться к базе данных! Проверьте правильность введенных данных или доступность сервера БД!"));
        return;
    }
    addLog(tr("Подключение к базе данных прошло успешно!"));
    
    QFile f("energo.escr");
    f.open(QIODevice::ReadOnly);
    
    QStringList script = QString(f.readAll()).split('\n');
    
    foreach (QString line, script)
    {
        if (line.at(0) == ';')
        {
            if (line.length() != 1)
                addLog(line.remove(0, 1));
        }
        else if (line.at(0) == '#')
        {
            continue;
        }
        else
        {
            PgreSqlResult * r = conn->exec(line);
            if (!r->isValid())
            {
                addLog(tr("Ошибка запроса! ").append(conn->getError()));
            }
            r->close();
        }
    }
    
    f.close();
    conn->close();
}

void MainWindow::createSlots()
{
    connect(ui->cmdInstall, SIGNAL(clicked(bool)), this, SLOT(commandInstall()));
    connect(ui->actAbout, SIGNAL(triggered(bool)), this, SLOT(actionAbout()));
    connect(ui->actExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}

void MainWindow::addLog(QString text)
{
    ui->txtLog->setPlainText(QString(ui->txtLog->toPlainText().append(text).append("\n")));
}
