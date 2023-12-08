#include "sample.h"
#include <math.h>
#include <QDebug>

Sample::Sample(Graph g) {
    this->G = g;
}

Sample::Sample(){

};

void Sample::draw(QPainter* painter, QRect window) {

    int count = this->G.getDim(); //количество точек графа

    qreal pSize = 20; //размер шрифта/радиус кругов
    if (count > 33 && count <= 66) pSize = 10;
    else if (count > 66) pSize = 5;

    qreal centerW = 0.5 * window.width();
    qreal centerH = 0.5 * window.height() + 15;
    qreal circleR = (centerW > centerH ? centerH : centerW) - 2*pSize - 50;
    qreal gap = 2.0 * acos(-1.0)/count; //интервал точек по кругу

    QFont font; //шрифт текста /ниже настройка
    font.setFamily("Consalas");
    font.setPointSize(pSize); //
    painter->setFont(font); //установка в пейнтер

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);
    pen.setBrush(QBrush(Qt::red));
    painter->setPen(pen);

    QPointF *t = new QPointF[count]; //массив для точек на кругу
    qreal x, y; //(для читаемости) координаты конкретной точки

    for (int i = 0; i < count; i++) {
        x = centerW + circleR*sin(i*gap);
        y = centerH - circleR*cos(i*gap);
        t[i] = QPointF(x, y);
    }

    for (int i = 0; i < count; i ++)
        for (int j = 0; j < count; j++)
            if (this->G.getElement(i,j) != 0)
                drawLines(t, painter, i, j, pSize);

    pen.setWidth(1);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::lightGray)); //цвет заливки

    for (int i=0; i<count; i++) {
        painter->setPen(QPen(Qt::darkGray)); //цвет линий
        painter->drawEllipse(t[i], pSize, pSize); //рисует в точке круг
        painter->setPen(QPen(Qt::black)); //цвет линий
        painter->drawText(QRectF(t[i].x()-pSize,t[i].y()-pSize, 2.0*pSize,2.0*pSize),
                          QString().setNum(i+1), QTextOption(Qt::AlignCenter));
    } //расстановка точек по кругу на расстоянии gap

    delete [] t; //массив точек удаляется
}

void Sample::drawLines(QPointF *t, QPainter *p, int i, int j, qreal radius){ // от i к j
    qreal angle = 2.0 * acos(-1.0)/this->G.getDim(); // pi/2 при 4 точках
    qreal circleX, circleY;
    if (i==j) {
        p->setBrush(QBrush());
        circleX = t[i].x() + radius*sin(i*angle); //cos(i*angle);
        circleY = t[i].y() - radius*cos(i*angle); //sin(i*angle);
        p->drawEllipse(QPointF(circleX,circleY), radius/2, radius/2);
        p->setBrush(QBrush(Qt::blue));
    } else {
        p->drawLine(t[i], t[j]);

        qreal k = (t[j].y() - t[i].y()) / (t[j].x() - t[i].x());

        if ((t[j].x() < t[i].x()) && t[j].y() > t[i].y()){
            circleX = t[j].x() + radius*cos((atan(k)));
            circleY = t[j].y() + radius*sin((atan(k)));

        } else if ((t[j].x() > t[i].x()) && t[j].y() > t[i].y()){
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() < t[i].x()) && t[j].y() < t[i].y()){
            circleX = t[j].x() + radius*cos(atan(k));
            circleY = t[j].y() + radius*sin(atan(k));

        } else if ((t[j].x() > t[i].x()) && t[j].y() < t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k));


        } else if ((t[j].x() == t[i].x()) && t[j].y() < t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k)) * 0;
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() == t[i].x()) && t[j].y() > t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k)) * 0;
            circleY = t[j].y() - radius*sin(atan(k));

        } else if ((t[j].x() > t[i].x()) && t[j].y() == t[i].y()) {
            circleX = t[j].x() - radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k)) * 0;

        } else if ((t[j].x() < t[i].x()) && t[j].y() == t[i].y()) {
            circleX = t[j].x() + radius*cos(atan(k));
            circleY = t[j].y() - radius*sin(atan(k)) * 0;

        } else {
            return;
        }
        p->drawEllipse(QPointF(circleX,circleY), radius/5,radius/5);
    }
}


