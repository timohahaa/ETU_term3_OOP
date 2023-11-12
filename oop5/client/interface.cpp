#include "interface.h"
#include "../common/common.h"
#include <QDebug>

Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Работа №3");
    setFixedSize(this->windowWidth, this->windowHeight);

    this->mainLayout = new QVBoxLayout(this);

    this->buttonLayout = new QHBoxLayout();
    this->setUpButtonLayout();

    this->matLayout = new QGridLayout();
    this->setUpMatLayout();

    this->mainLayout->addLayout(this->matLayout);
    this->mainLayout->addLayout(this->buttonLayout);

    // теперь подключаем сигналы
    connect(this->buttonCalcDeterminand, SIGNAL(pressed()), this,SLOT(sendRequest()));
    connect(this->buttonCalcRank, SIGNAL(pressed()), this,SLOT(sendRequest()));
    connect(this->buttonTranspose, SIGNAL(pressed()), this,SLOT(sendRequest()));
    connect(this->matSize, SIGNAL(valueChanged(int)), this,SLOT(changeSize()));
}

Interface::~Interface()
{
    this->clearMatLayout();
    delete this->mainLayout;
    delete this->matLayout;
    delete this->buttonLayout;
    delete this->matSize;
//    delete this->output;
    delete this->buttonCalcDeterminand;
    delete this->buttonCalcRank;
    delete this->buttonTranspose;
}

void Interface::setUpButtonLayout()
{
    // тикер для размера матрицы
    this->matSize = new QSpinBox();
    this->matSize->setMinimum(1);
    this->matSize->setMaximum(5);
    this->matSize->setValue(3);
//    // output label
//    this->output = new QLabel("Результат: ");
    // кнопки действий
    this->buttonCalcDeterminand = new QPushButton("Определитель");
    this->buttonCalcRank = new QPushButton("Ранг");
    this->buttonTranspose = new QPushButton("Транспонировать");
    // лейбл для спинбокса
    QLabel *l = new QLabel("Размер матрицы");
    // добавляем все кнопки
    this->buttonLayout->addWidget(l);
    this->buttonLayout->addWidget(this->matSize);
    this->buttonLayout->addWidget(this->buttonCalcDeterminand);
    this->buttonLayout->addWidget(this->buttonCalcRank);
    this->buttonLayout->addWidget(this->buttonTranspose);
//    this->buttonLayout->addWidget(this->output);
}

void Interface::setUpMatLayout()
{
    QRegularExpression re("-?[0-9]*\\/[1-9]+[0-9]*");
    QRegularExpressionValidator *v = new QRegularExpressionValidator(re);
    int size = this->matSize->value();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            QLineEdit *le = new QLineEdit();
            le->setValidator(v);
            this->matLayout->addWidget(le, i, j);
        }
    }
}

void Interface::clearMatLayout()
{
    for(int i = this->matLayout->count() -1; i > -1; i--)
    {
        QLayoutItem *item = this->matLayout->takeAt(i);
        if(!item)
        {
            continue;
        }
        this->matLayout->removeWidget(item->widget());
        delete item->widget();
        this->matLayout->removeItem(item);
        delete item;
    }
}

QString Interface::getMatrixFromLayout()
{
    int size = this->matSize->value();
    QString mat;
    mat += QString::number(size);
    mat += separator;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            QLineEdit *num = (QLineEdit*)this->matLayout->itemAtPosition(i, j)->widget();
            mat += num->text();
            mat += separator;
        }
    }
    return mat;
}

void Interface::changeSize()
{
    this->clearMatLayout();
    delete this->matLayout;
    this->matLayout = new QGridLayout();
    this->setUpMatLayout();
    this->mainLayout->insertLayout(0, this->matLayout);
}

void Interface::onResponce(QByteArray msg)
{
    QString m(msg);
    QStringList parts = m.split(separator, Qt::SkipEmptyParts);
    switch (parts[0].toInt()) {
    case DETERMINAND_RESP:
    {
        QMessageBox::information(this, "Результат", parts[1]);
    }
        break;
    case RANK_RESP:
    {
        QMessageBox::information(this, "Результат", parts[1]);
    }
        break;
    case TRANSPOSE_RESP:
    {
        auto rowFrom1Dindex = [](int idx, int size)
        {
            return idx / size;
        };
        auto colFrom1Dindex = [](int idx, int size)
        {
            return idx % size;
        };

        int size = parts[1].toInt();
        int idx = 0;
        int k = 2;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                QString numStr = parts[k];
                QLineEdit *le = (QLineEdit*)this->matLayout->itemAt(idx)->widget();
                le->setText(numStr);
                idx++;
                k++;
            }
        }
    }
        break;
    default:
        break;
    }
}

void Interface::sendRequest()
{
    QString req;
    QPushButton *btn = (QPushButton*)sender();
    if(btn == this->buttonCalcDeterminand)
    {
        req += QString::number(DETERMINAND_REQ);
        req += separator;
        req += this->getMatrixFromLayout();
    }
    if(btn == this->buttonCalcRank)
    {
        req += QString::number(RANK_REQ);
        req += separator;
        req += this->getMatrixFromLayout();
    }
    if(btn == this->buttonTranspose)
    {
        req += QString::number(TRANSPOSE_REQ);
        req += separator;
        req += this->getMatrixFromLayout();
    }

    qDebug() << req;
    emit request(req);
}
