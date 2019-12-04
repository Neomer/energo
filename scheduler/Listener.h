#ifndef LISTENER_H
#define LISTENER_H

#include <QTcpServer>

class Listener : public QTcpServer
{
    Q_OBJECT
public:
    explicit Listener(QObject *parent = 0);

signals:

public slots:

};

#endif // LISTENER_H
