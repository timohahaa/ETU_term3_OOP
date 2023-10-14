#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "../common/communicator.h"
#include "../common/common.h"
#include "matrix.h"

struct ParsedMessage
{
    message msg_type;
    Matrix mat;
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
    QString transposeMessage(Matrix mat);

private slots:

};

#endif // APPLICATION_H
