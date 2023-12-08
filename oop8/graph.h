#ifndef GRAPH_H
#define GRAPH_H
#include "matrix.h"
#include <QFile>
#include <QTextStream>


class Graph
{
protected:
    Matrix<int> adjMatrix;
    int dim = 3;
public:
    Graph();
    void setGraph(QString);
    int getDim();
    int getElement(int, int);

};

#endif
