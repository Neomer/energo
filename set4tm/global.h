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
���������� ��������, ���/���?�(���/����?�):
0 � 5000 ���/���?�;
1 � 25000 ���/���?�;
2 � 1250 ���/���?�;
3 � 6250 ���/���?�;
4 � 500 ���/���?�
5 � 250 ���/���?�
6 � 6400 ���/���?�;
*/ 
// TODO: ������� ����������� ������� ������� ��-�� ���/���*�

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
