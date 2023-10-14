#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

struct ConnectionParametrs
{
    QHostAddress selfAddr;
    quint16 selfPort;
    QHostAddress remoteAddr;
    quint16 remotePort;
};

class Communicator : public QUdpSocket
{
    Q_OBJECT

public:
    Communicator(ConnectionParametrs params, QObject *parent = nullptr);
    bool isSuccesfullyConnected();

public slots:
    void sendMsg(QByteArray msg);

signals:
    void receivedMsg(QByteArray msg);

private:
    bool isReady;
    ConnectionParametrs connParams;

private slots:
    void msgReceived();
};

#endif // COMMUNICATOR_H
