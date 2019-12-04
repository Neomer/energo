#include <QtCore/QCoreApplication>
#include <qextserialport.h>
#include <QDebug>
#include <QByteArray>
#include <QTextEncoder>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	QextSerialPort *port = new QextSerialPort("COM1", QextSerialPort::Polling);
	port->setBaudRate(BAUD9600);
    port->setFlowControl(FLOW_HARDWARE);
    port->setParity(PAR_NONE);
    port->setDataBits(DATA_8);
    port->setStopBits(STOP_1);
	port->setTimeout(500);
	if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered)) {
        if (!(port->lineStatus() & LS_DSR))
            qDebug() << "warning: device is not turned on";
        qDebug() << "listening for data on" << port->portName();
    }
    else {
        qDebug() << "device failed to open:" << port->errorString();
    }
	qDebug("Baud rate: %i", port->baudRate());
	QString buf = "AT";
	buf.append('\x0D').append('\x0A');
	int sent = port->write(buf.toAscii().constData(), buf.length());
	if (sent < 0)
		qWarning() << "Error: " << port->errorString();
	else
		qWarning("Sent: %i byte(s)", sent);
	
	char ba[1024];
	int av;
	while ((av = port->bytesAvailable()) == 0);
	qWarning("Available %i byte(s)", av);
	port->read(ba, av);
	ba[av] = 0;
	qWarning("%s", ba);
	port->close();

    return a.exec();
}
