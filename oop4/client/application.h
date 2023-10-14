#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QApplication>
#include "interface.h"
#include "../common/communicator.h"


class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int argc, char** argv);

public slots:

signals:

private:
    Communicator *communicator;
    Interface *interface;

private slots:
    void sendRequest(QString req);

};

#endif // APPLICATION_H
