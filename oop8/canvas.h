#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include <QMouseEvent>
#include "stategraph.h"

class Interface : public QWidget {
    Q_OBJECT
    StateGraph sample;

public:
    Interface(StateGraph,QWidget *parent = 0);
    ~Interface();

public slots:
    void browse();

protected:
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent*);
    QWidget canvas;


};

#endif
