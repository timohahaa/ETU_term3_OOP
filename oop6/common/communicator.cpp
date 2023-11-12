#include "communicator.h"

Communicator::Communicator(ConnectionParametrs params, QObject *parent)
    : QUdpSocket(parent)
{
    this->connParams = params;
    this->isReady = this->bind(this->connParams.selfAddr, this->connParams.selfPort,
                               QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);

    if(this->isReady)
    {
        connect(this, SIGNAL(readyRead()), this, SLOT(msgReceived()));
    }
}

bool Communicator::isSuccesfullyConnected()
{
    return this->isReady;
}

void Communicator::sendMsg(QByteArray msg)
{
    if(this->isReady)
    {
        this->writeDatagram(msg, this->connParams.remoteAddr, this->connParams.remotePort);
    }
}

void Communicator::msgReceived()
{
    if(this->hasPendingDatagrams())
    {
        quint64 size = this->pendingDatagramSize();
        QByteArray msg(size, '\0');
        this->readDatagram(msg.data(), size);
        // отправляем сигнал с сообщением
        emit receivedMsg(msg);
    }
}

