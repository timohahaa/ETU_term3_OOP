#ifndef INTERFACE_H
#define INTERFACE_H

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

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

public slots:
    void changeSize();
    void onResponce(QByteArray msg);

signals:
    void request(QString req);

private:
    int windowWidth = 600;
    int windowHeight = 400;
    // основной лэйаут
    QVBoxLayout *mainLayout;
    // лейаут для матрицы
    QGridLayout *matLayout;
    // лейаут для кнопок и вывода
    QHBoxLayout *buttonLayout;
    // кнопки и прочее
    QSpinBox *matSize;
//    QLabel *output;
    QPushButton *buttonCalcDeterminand;
    QPushButton *buttonCalcRank;
    QPushButton *buttonTranspose;

    void setUpButtonLayout();
    void setUpMatLayout();
    void clearMatLayout();
    QString getMatrixFromLayout();

private slots:
    void sendRequest();

};
#endif // INTERFACE_H
