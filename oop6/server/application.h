#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include "../common/communicator.h"
#include "../common/common.h"
#include "squarematrix.h"

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

    template <class number>
    SquareMatrix<number> parseMessage(QByteArray msg);

    template <class number>
    QString transposeMessage(SquareMatrix<number> mat);

private slots:

};

#endif // APPLICATION_H
