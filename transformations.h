#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <QPointF>
#include <vector>

struct Rect
{
    QPointF point;
    double width;
    double height;
    Rect(QPointF point, double width, double height):
        point(point), width(width), height(height){}
};

namespace transformation
{
    Rect world = {QPointF{-180.0, 90.0}, 360.0, 180.0};
    Rect window = world;
    Rect viewPort = {QPointF{0.0, 0.0}, 800.0, 600.0};
}

using namespace transformation;

double radius = 10;

QPointF windowToViewPort(QPointF windowPoint)
{
    QPointF view;
    view.setX(((viewPort.width * (windowPoint.x() - window.point.x())) +  (viewPort.point.x() * window.width)) / window.width);
    view.setY(((viewPort.height * (window.point.y() - windowPoint.y()))  + (viewPort.point.y() * window.height)) / window.height);
    return view;
}

QPointF viewPortToWindow(QPointF viewPoint)
{
    QPointF windowPoint;
    windowPoint.setX((((viewPoint.x() - viewPort.point.x()) * window.width) + viewPort.width * window.point.x()) / viewPort.width);
    windowPoint.setY(((viewPort.height * window.point.y()) - ((viewPoint.y() - viewPort.point.y()) * window.height)) / viewPort.height);
    return windowPoint;
}

std::vector<QPointF> getVectorAsWindowPoints(const std::vector<QPointF>& viewPortPoints)
{
    std::vector<QPointF> points;

    for (auto &point: viewPortPoints)
    {
        points.push_back(viewPortToWindow(point));
    }

    return points;
}

#endif // TRANSFORMATIONS_H
