#include "interface.h"
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

//    this->outputLayout = new QHBoxLayout();
//    this->output = new QLabel("Результат: ");
//    this->outputLayout->addWidget(this->output);

    this->mainLayout->addLayout(this->matLayout);
    this->mainLayout->addLayout(this->buttonLayout);
//    this->mainLayout->addLayout(this->outputLayout);

    // теперь подключаем сигналы
    connect(this->buttonCalcDeterminand, SIGNAL(pressed()), this,SLOT(calcDeterminand()));
    connect(this->buttonCalcRank, SIGNAL(pressed()), this,SLOT(calcRank()));
    connect(this->buttonTranspose, SIGNAL(pressed()), this,SLOT(transpose()));
    connect(this->matSize, SIGNAL(valueChanged(int)), this,SLOT(changeSize()));
}

Interface::~Interface()
{
    this->clearMatLayout();
    delete this->mainLayout;
    delete this->matLayout;
    delete this->buttonLayout;
//    delete this->output;
//    delete this->outputLayout;
    delete this->matSize;
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

Matrix Interface::getMatrixFromMatLayout()
{
    int size = this->matSize->value();
    Matrix mat;
    mat.setSize(size);
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            QLineEdit *le = qobject_cast<QLineEdit*>(this->matLayout->itemAtPosition(i, j)->widget());
            Rational r(le->text().toStdString());
            mat.setAtIdx(r, i, j);
        }
    }
    return mat;
}

void Interface::layoutFromMatrix(Matrix mat)
{
    int size = this->matSize->value();
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            QLineEdit *le = qobject_cast<QLineEdit*>(this->matLayout->itemAtPosition(i, j)->widget());
            QString num;
            num << mat.atIdx(i, j);
            le->setText(num);
        }
    }
}

void Interface::calcDeterminand()
{
    Matrix mat = this->getMatrixFromMatLayout();
    number det = mat.calcDeterminand();
    QString str;
    str << det;
    QMessageBox::information(this, "Результат", str);
}

void Interface::calcRank()
{
    Matrix mat = this->getMatrixFromMatLayout();
    int rank = mat.calcRank();
    QMessageBox::information(this, "Результат", QString::number(rank));
}

void Interface::transpose()
{
    Matrix mat = this->getMatrixFromMatLayout();
    Matrix transposed = mat.transposed();
    this->layoutFromMatrix(transposed);
}

void Interface::changeSize()
{
    this->clearMatLayout();
    delete this->matLayout;
    this->matLayout = new QGridLayout();
    this->setUpMatLayout();
    this->mainLayout->insertLayout(0, this->matLayout);
}


















