#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QFileDialog>
#include <QToolButton>
#include "sample.h"

class Interface : public QWidget {
    Q_OBJECT
    Sample sample;

public:
    Interface(Sample,QWidget *parent = 0);
    ~Interface();

public slots:
    void browse();

protected:
    void paintEvent(QPaintEvent*);
    QWidget canvas;


};

#endif
