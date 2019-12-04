#ifndef QGSMSENDER_H
#define QGSMSENDER_H

#include <QThread>

class GSMSender : public QThread
{
    Q_OBJECT
public:
    explicit QGSMSender(QObject *parent = 0);

signals:

public slots:

	
protected:
	void run();
};

#endif // QGSMSENDER_H
