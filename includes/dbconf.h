#ifndef DBCONF_H
#define DBCONF_H

#include <QFile>

static QString DB_HOST;
static void initdbhost()
{
	QFile file("db");
	file.open(QIODevice::ReadOnly);
	DB_HOST = file.readLine();
}


#define DB_USER "postgres"
#define DB_PASS "1234"
#define DB_NAME "energo"

#endif // DBCONF_H
