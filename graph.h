#ifndef GRAPH_H
#define GRAPH_H
#include "Polynomial.h"
#include "qcustomplot.h"

class Graph
{
    void print(Polynomial p, double xBegin, double xEnd, QCustomPlot *customPlot);
public:
    Graph(Polynomial p, double xBegin, double xEnd, QCustomPlot *customPlot) {print(p, xBegin, xEnd, customPlot);}
};

#endif // GRAPH_H
