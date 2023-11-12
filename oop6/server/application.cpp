#include <QDebug>
#include "application.h"
#include "../common/common.h"

Application::Application(int argc, char **argv)
    : QCoreApplication(argc, argv)
{
    ConnectionParametrs connParams = {
        QHostAddress("127.0.0.1"),
        10000,
        QHostAddress("127.0.0.1"),
        10001
    };

    this->communicator = new Communicator(connParams, this);

    if(this->communicator->isSuccesfullyConnected())
    {
        connect(this->communicator, SIGNAL(receivedMsg(QByteArray)), this, SLOT(receiveMsg(QByteArray)));
    }
}

void Application::receiveMsg(QByteArray msg)
{
    ParsedMessage pm = this->parseMessage(msg);
    QString answer;
    switch (pm.msg_type) {
    case DETERMINAND_REQ:
    {
        number det = pm.mat.calcDeterminand();
        QString detStr;
        detStr << det;
        answer += QString::number(DETERMINAND_RESP);
        answer += separator;
        answer += detStr;
        answer += separator;
    }
    break;
    case RANK_REQ:
    {
        int rank = pm.mat.calcRank();
        answer += QString::number(RANK_RESP);
        answer += separator;
        answer += QString::number(rank);
        answer += separator;
    }
    break;
    case TRANSPOSE_REQ:
    {
        SquareMatrix transposed(pm.mat.transposed());
        answer = this->transposeMessage(transposed);
    }
    break;
    default:
        break;
    }
    qDebug() << answer;
    this->communicator->sendMsg(answer.toUtf8());
}

// msg_type(sep)mat_size(sep)...mat_values...(sep)
ParsedMessage Application::parseMessage(QByteArray msg)
{
    auto rowFrom1Dindex = [](int idx, int size)
    {
        return idx / size;
    };
    auto colFrom1Dindex = [](int idx, int size)
    {
        return idx % size;
    };

    ParsedMessage pm;
    SquareMatrix mat;
    QString m(msg);
    qDebug() << m;
    QStringList parts = m.split(separator, Qt::SkipEmptyParts);
    qDebug() << parts;
    pm.msg_type = message(parts[0].toInt());
    int size = parts[1].toInt();
    mat.setSize(size);
    int idx = 0;
    int k = 2;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            QString numStr = parts[k];
            number num(numStr.toStdString());
            mat.setAtIdx(num,
                         rowFrom1Dindex(idx, size),
                         colFrom1Dindex(idx, size));

            idx++;
            k++;
        }
    }

    //   mat.printMatrix();
    pm.mat = mat;
    return pm;
}

QString Application::transposeMessage(SquareMatrix mat)
{
    QString answer;
    answer += QString::number(TRANSPOSE_RESP);
    answer += separator;
    int size = mat.getSize();
    answer += QString::number(size);
    answer += separator;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            number num = mat.atIdx(i, j);
            QString numStr;
            numStr << num;
            answer += numStr;
            answer += separator;
        }
    }
    //    qDebug() << answer;
    return answer;
}
