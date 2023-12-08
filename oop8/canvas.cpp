#include "canvas.h"

Interface::Interface(StateGraph f, QWidget *parent) : QWidget(parent) {
    sample = f;
    setFixedSize(640,480);
    QToolButton* someButton = new QToolButton(this);
    someButton->setGeometry(5, 5, 630, 20);
    someButton->setText("Выберите файл с графом");
    connect(someButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void Interface::browse(){
    QString fileName = "";
    fileName = QFileDialog::getOpenFileName(this, ("Open File"), "", ("Text files (*txt)"));
    if (fileName != ""){
        Graph g;
        g.setGraph(fileName);
        this->sample = StateGraph(g);
        repaint();
    } else return;
}

Interface::~Interface(){}

void Interface::paintEvent(QPaintEvent*) {
    QPainter p;
    p.begin(this);
    sample.draw(&p, QRect(5, 30, 630, 450)); //вызывает функцию отрисовки
    p.end();
}

void Interface::mousePressEvent(QMouseEvent* event){ // вот тут обработчик нажатия на клавишу
    if (event->button() == Qt::LeftButton)  sample.onClickedEvent(false);
    if (event->button() == Qt::RightButton) sample.onClickedEvent(true);
    update();
} // я не знаю, надо ли нам снова писать в отчете про canvas. Наверное дааа, раз тут поменялось чет,
// но по большей части можно скопировать со старого отчета
