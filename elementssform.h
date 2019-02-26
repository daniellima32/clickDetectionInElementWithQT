#ifndef ELEMENTSSFORM_H
#define ELEMENTSSFORM_H

#include <QPointF>
#include <vector>

std::vector<QPointF> getDemandPoints(QPointF point, double radius)
{
    std::vector<QPointF>points =
    {
        QPointF(point.x(), point.y()-radius),   //p1
        QPointF(point.x()+radius, point.y()),   //p2
        QPointF(point.x(), point.y()+radius),  //p3
        QPointF(point.x()-radius, point.y())  //p4
    };

    return points;
}

std::vector<QPointF> getReservoirPoints(QPointF point, double radius)
{
    std::vector<QPointF>points =
    {
        QPointF(point.x(), point.y()-radius),   //p1
        QPointF(point.x()+radius, point.y()+radius),   //p2
        QPointF(point.x()-radius, point.y()+radius)  //p3
    };

    return points;
}

#endif // ELEMENTSSFORM_H
