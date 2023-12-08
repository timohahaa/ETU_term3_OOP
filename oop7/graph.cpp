#include "graph.h"
#include <QDebug>

Graph::Graph()
{

}

void Graph::setGraph(QString f){
    QFile file(f);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);

    this->dim = in.readLine().toInt();
    this->adjMatrix.setColumnCount(this->dim);
    this->adjMatrix.setRowCount(this->dim);
    QStringList matr = in.readLine().split(" "), matr2;
    int count = 0;
    for (int i = 0; i < this->dim; i++){
        for (int j = 0; j < this->dim; j++){
           this->adjMatrix.setAtIdx(matr[count].toInt(), i, j);
           count++;
        }
    }
    file.close();
}

int Graph::getDim(){
    return this->dim;
}

int Graph::getElement(int i, int j){
    return this->adjMatrix.atIdx(i, j);
}


