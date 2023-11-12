#include <QDebug>
#include "application.h"
#include "../common/common.h"
#include "rational.h"
#include "complex.h"
#include "float.h"

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
    QString answer;
    QString m(msg);
    QStringList parts = m.split(separator, Qt::SkipEmptyParts);
    type num_type = type(parts[0].toInt());
    message msg_type = message(parts[1].toInt());
    switch (msg_type) {
    case DETERMINAND_REQ:
    {
        if(num_type == TYPE_RATIONAL)
        {
            SquareMatrix<Rational> mat = this->parseMessage<Rational>(msg);
            std::cout <<" - " << mat.getSize()<<std::endl;
            Rational det = mat.calcDeterminand();
            QString detStr;
            detStr << det;
            answer += QString::number(DETERMINAND_RESP);
            answer += separator;
            answer += detStr;
            answer += separator;
        }
        else if(num_type == TYPE_COMPLEX)
        {
            SquareMatrix<Complex> mat = this->parseMessage<Complex>(msg);
            Complex det = mat.calcDeterminand();
            QString detStr;
            detStr << det;
            answer += QString::number(DETERMINAND_RESP);
            answer += separator;
            answer += detStr;
            answer += separator;
        }
        else if(num_type == TYPE_FLOAT)
        {
            SquareMatrix<Float> mat = this->parseMessage<Float>(msg);
            Float det = mat.calcDeterminand();
            QString detStr;
            detStr << det;
            answer += QString::number(DETERMINAND_RESP);
            answer += separator;
            answer += detStr;
            answer += separator;
        }
    }
    break;
    case RANK_REQ:
    {
        if(num_type == TYPE_RATIONAL)
        {
            SquareMatrix<Rational> mat = this->parseMessage<Rational>(msg);
            int rank = mat.calcRank();
            answer += QString::number(RANK_RESP);
            answer += separator;
            answer += QString::number(rank);
            answer += separator;
        }
        else if(num_type == TYPE_COMPLEX)
        {
            SquareMatrix<Complex> mat = this->parseMessage<Complex>(msg);
            int rank = mat.calcRank();
            answer += QString::number(RANK_RESP);
            answer += separator;
            answer += QString::number(rank);
            answer += separator;
        }
        else if(num_type == TYPE_FLOAT)
        {
            SquareMatrix<Float> mat = this->parseMessage<Float>(msg);
            int rank = mat.calcRank();
            answer += QString::number(RANK_RESP);
            answer += separator;
            answer += QString::number(rank);
            answer += separator;
        }
    }
    break;
    case TRANSPOSE_REQ:
    {
        if(num_type == TYPE_RATIONAL)
        {
            SquareMatrix<Rational> mat = this->parseMessage<Rational>(msg);
            SquareMatrix transposed(mat.transposed());
            answer = this->transposeMessage(transposed);
        }
        else if(num_type == TYPE_COMPLEX)
        {
            SquareMatrix<Complex> mat = this->parseMessage<Complex>(msg);
            SquareMatrix transposed(mat.transposed());
            answer = this->transposeMessage(transposed);
        }
        else if(num_type == TYPE_FLOAT)
        {
            SquareMatrix<Float> mat = this->parseMessage<Float>(msg);
            SquareMatrix transposed(mat.transposed());
            answer = this->transposeMessage(transposed);
        }
    }
    break;
    default:
        break;
    }
    qDebug() << answer;
    this->communicator->sendMsg(answer.toUtf8());
}

template<class number>
QString Application::transposeMessage(SquareMatrix<number> mat)
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
    return answer;
}

template<class number>
SquareMatrix<number> Application::parseMessage(QByteArray msg)
{
    auto rowFrom1Dindex = [](int idx, int size)
    {
        return idx / size;
    };
    auto colFrom1Dindex = [](int idx, int size)
    {
        return idx % size;
    };

    QString m(msg);
    QStringList parts = m.split(separator, Qt::SkipEmptyParts);
    type num_type = type(parts[0].toInt());
    message msg_type = message(parts[1].toInt());
    SquareMatrix<number> mat;
    int size = parts[2].toInt();
    mat.setSize(size);
    int idx = 0;
    int k = 3;
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
    return mat;
}
