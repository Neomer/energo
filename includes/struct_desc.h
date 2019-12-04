#ifndef STRUCT_DESC_H
#define STRUCT_DESC_H

#include <QTreeWidgetItem>

enum StructType
{
	ST_Factory,
	//ST_GTP,
	ST_Object,
	ST_Feeder,
	ST_Counter
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

struct GTP
{
    int ID;
    QString name;
};

struct Object
{
    int ID;
    QString name;
};

struct Counter
{
    int ID;
    qint64 number;
};

struct Feeder
{
    int ID;
    QString name;
};


Q_DECLARE_METATYPE(Factory)
Q_DECLARE_METATYPE(Counter)
Q_DECLARE_METATYPE(Object)
Q_DECLARE_METATYPE(GTP)
Q_DECLARE_METATYPE(Feeder)
Q_DECLARE_METATYPE(TVItemDesc)

#endif // STRUCT_DESC_H
