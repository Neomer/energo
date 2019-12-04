#ifndef STRUCT_DESC_H
#define STRUCT_DESC_H

#include <QTreeWidgetItem>

enum StructType
{
	ST_Organization,
	ST_Factory,
	//ST_GTP,
	ST_Object,
	ST_Feeder,
	ST_Counter,
	ST_Channel,
	ST_BalansElement
};

enum BalansType
{
	BT_Root,
	BT_Element
};

struct TVItemDesc
{
	StructType type;
	void * link;
};

struct Factory
{
    int ID;
    QString name;
};

struct Object
{
    int ID;
    QString name;
};

struct Feeder
{
    int ID;
    QString name;
};

struct Counter
{
    int ID;
    qint64 number;
};

struct Channel
{
	int ID;
	QString name;
};

struct Schedule
{
	int ID;
	//QString name;
};

Q_DECLARE_METATYPE(Factory)
Q_DECLARE_METATYPE(Counter)
Q_DECLARE_METATYPE(Object)
Q_DECLARE_METATYPE(Feeder)
Q_DECLARE_METATYPE(TVItemDesc)

#endif // STRUCT_DESC_H
