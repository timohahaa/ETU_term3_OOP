#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "../common/communicator.h"
#include "../common/common.h"
#include "squarematrix.h"

struct ParsedMessage
{
    message msg_type;
    SquareMatrix mat;
};

class Application : public QCoreApplication
{
    Q_OBJECT

public:
    Application(int argc, char** argv);

public slots:
    void receiveMsg(QByteArray msg);

signals:

private:
    Communicator *communicator;
    ParsedMessage parseMessage(QByteArray msg);
    QString transposeMessage(SquareMatrix mat);

private slots:

};

#endif // APPLICATION_H
