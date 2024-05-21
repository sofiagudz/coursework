#include "graph.h"

void Graph::print(Polynomial p, double xBegin, double xEnd , QCustomPlot *customPlot)
{
    QVector<double> x, y;
    double h, X;

    h = 0.1;

    for(X = xBegin; X <= xEnd; X += h){
        x.push_back(X);
        y.push_back(p.solve(X));
    }

    customPlot->addGraph();

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    pen.setStyle(Qt::SolidLine);
    customPlot->graph(0)->setPen(pen);

    customPlot->rescaleAxes();
    customPlot->graph(0)->setData(x, y);
    customPlot->replot();
}
