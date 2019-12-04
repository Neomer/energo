#ifndef GSMCONNECTION_H
#define GSMCONNECTION_H

#include <QObject>
#include <qextserialport.h>

enum GSMConnectionState
{
	GCS_INITIALIZATION,
	GCS_CONNECTING,
	GCS_DATA
};

/*!
  Класс обеспечивает содеинение между двумя GSM-модемами, 
  подключенными к COM-порту.
 */
class GSMConnection : public QObject
{
public:
	GSMConnection(QString name, PortSettings settings);
    GSMConnection(QString name, PortSettings settings, QString init_string);
	QString GetLastError();
	bool Initialize(QString init_string);
	static const char * addCRLF(QString text)
	{
		text.append("\x0D\x0A");
		return text.toAscii().constData();
	}
	
private slots:
	void onReadyRead();	

protected:
	QextSerialPort *port;
	PortSettings sets;
	QString err;
	GSMConnectionState state;
};

#endif // GSMCONNECTION_H
