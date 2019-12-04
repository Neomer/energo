#ifndef SET4_GLOBAL_H
#define SET4_GLOBAL_H

#include <QDateTime>
#include <QMap>

#define SET4TM_DATASIZE		8

enum Set4tmDayLigtht
{
	Summer,
	Winter
};

enum Set4tmDayOfWeek
{
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};

struct Set4tmResponse
{
	char address;
	char code;
	char * data;
};


/*
ѕосто€нна€ счетчика, имп/к¬т?ч(имп/квар?ч):
0 Ц 5000 имп/к¬т?ч;
1 Ц 25000 имп/к¬т?ч;
2 Ц 1250 имп/к¬т?ч;
3 Ц 6250 имп/к¬т?ч;
4 Ц 500 имп/к¬т?ч
5 Ц 250 имп/к¬т?ч
6 Ц 6400 имп/к¬т?ч;
*/ 
// TODO: —делать возможность ручного задани€ кл-ва имп/к¬т*ч

class Set4tmDescription
{
	Set4tmDescription(QString name, quint16 A, byte buffer_size)
	{
		this->name = name;
		this->A = A;
		this->buffer_size = buffer_size;
	}
	
public:
	QString name;
	quint16 A;
	byte buffer_size;
};

static QMap<byte, int> Set4tmConstA;
static byte Set4tmBufferSize[0x0F];


#endif // GLOBAL_H
