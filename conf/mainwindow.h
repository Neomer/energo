#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QListWidgetItem>

#include "../pgredrv/PgreSqlDrv.h"

#include "../includes/pgre/libpq-fe.h"
#include "struct_desc.h"
#include "debugwindow.h"
#include "ChannelsSets.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setDBConnection(PgreSqlDrv *connection);
    void updateList(QTreeWidgetItem * item, int column);
	void updateBalans(QTreeWidgetItem * item, int column);
	void updateDPG(QTreeWidgetItem * item, int column);
	void updateSchedule(QTreeWidgetItem *parent, int column);
	void updateChannels(QTreeWidgetItem *parent, int column);
	void updateUsers(QTreeWidgetItem *parent, int column);
	void updateHolydays(QTreeWidgetItem *parent, int column);
	void setDebugWindow(DebugWindow * dbg);
    ~MainWindow();

public slots:
    void export_conf();
    void login_fail();
	void db_connected(PgreSqlDrv * connection);
	void twItemSelected(QTreeWidgetItem * item, int column);
	void twItemClicked(QTreeWidgetItem * item, int column);

	void twScheduleItemSelected(QTreeWidgetItem* item, int column);
	void addScheduleItem(QTreeWidgetItem * parent);
	
	void twChannelsItemSelected(QTreeWidgetItem* item, int column);
	void addChannelsItem(QTreeWidgetItem * parent);
	
	void twBalansItemSelected(QTreeWidgetItem * item, int column);
	void twBalansItemClicked(QTreeWidgetItem * item, int column);
	void addTwBalansItem(QTreeWidgetItem * parent);

	void twDPGItemSelected(QTreeWidgetItem * item, int column);
	void twDPGItemClicked(QTreeWidgetItem * item, int column);
	void addTwDPGItem(QTreeWidgetItem * parent);
	
	void twUsersItemSelected(QTreeWidgetItem * item, int column);
	void twUsersItemClicked(QTreeWidgetItem * item, int column);
	void addTwUsersItem(QTreeWidgetItem * parent);

	void twHolyItemSelected(QTreeWidgetItem * item, int column);
	void twHolyItemClicked(QTreeWidgetItem * item, int column);
	void addTwHolyItem(QTreeWidgetItem * parent);

	void onDebugHide();
	void login_form_close();
	void addTwItem(QTreeWidgetItem * parent);
	void actFindClicked();
	void findElement();
	void channelSets();
	
signals:
	void onClose();

private:
    Ui::MainWindow *ui;
    QList<Factory *> f;
	QTextCodec * codec;
	DebugWindow * m_dbg;
	PgreSqlDrv * m_conn;
};

#endif // MAINWINDOW_H
