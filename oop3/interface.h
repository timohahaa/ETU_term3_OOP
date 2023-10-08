#ifndef INTERFACE_H
#define INTERFACE_H

#include "matrix.h"
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QRect>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>

class Interface : public QWidget
{
    Q_OBJECT

private:
    int windowWidth = 600;
    int windowHeight = 400;
    // основной лэйаут
    QVBoxLayout *mainLayout;
    // лейаут для матрицы
    QGridLayout *matLayout;
    // лейаут для кнопок
    QHBoxLayout *buttonLayout;
//    // лейаут для вывода
//    QHBoxLayout *outputLayout;
//    QLabel *output;
    // кнопки и прочее
    QSpinBox *matSize;
    QPushButton *buttonCalcDeterminand;
    QPushButton *buttonCalcRank;
    QPushButton *buttonTranspose;

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

    void setUpButtonLayout();
    void setUpMatLayout();
    void clearMatLayout();
    Matrix getMatrixFromMatLayout();
    void layoutFromMatrix(Matrix mat);

public slots:
    void calcDeterminand();
    void calcRank();
    void transpose();
    void changeSize();
};
#endif // INTERFACE_H
