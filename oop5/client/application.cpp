#include "application.h"

Application::Application(int argc, char** argv)
    : QApplication(argc, argv)
{
    ConnectionParametrs connParams = {
        QHostAddress("127.0.0.1"),
        10001,
        QHostAddress("127.0.0.1"),
        10000
    };

    this->interface = new Interface();

    this->communicator = new Communicator(connParams, this);
    if(this->communicator->isSuccesfullyConnected())
    {
        connect(this->interface, SIGNAL(request(QString)), this, SLOT(sendRequest(QString)));
        connect(this->communicator, SIGNAL(receivedMsg(QByteArray)), this->interface, SLOT(onResponce(QByteArray)));
    }

    this->interface->show();
}

void Application::sendRequest(QString req)
{
    this->communicator->sendMsg(req.toUtf8());
}
