#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>

#include "transformations.h"
#include "elementssform.h"

#include <iostream>
using namespace std;

#include <QPainter>

#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    refreshPixmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void printPointData(QPointF viewPortPos)
{
    cout << "point in Viewport (" << viewPortPos.x() << ", " << viewPortPos.y() << ")" << endl;
    QPointF windowPoint = viewPortToWindow(viewPortPos);
    cout << "point in Window (" << windowPoint.x() << ", " << windowPoint.y() << ")" << endl;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPointF viewPortPos = {static_cast<double>(event->x()),
                static_cast<double>(event->y())};

    printPointData(viewPortPos);
    checkClickInElement(viewPortPos);
}

void MainWindow::refreshPixmap()
{
    //Desenhar demanda
    this->pixmap = QPixmap(size());
    this->pixmap.fill(Qt::white);

    QPainter painter(&this->pixmap);
    painter.initFrom(this);

    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));

    std::vector<QPointF> vecDemandPoints =
            getDemandPoints(windowToViewPort(this->demand), this->demandRadius);
    painter.drawConvexPolygon(
                vecDemandPoints.data(),    //Pontos
                vecDemandPoints.size()     //Quantidade de pontos
    );

    painter.setBrush(QBrush(QColor(20, 170, 255), Qt::SolidPattern));

    std::vector<QPointF> vecReservoirPoints =
            getReservoirPoints(windowToViewPort(this->reservoir), this->reservoirRadius);
    painter.drawConvexPolygon(
                vecReservoirPoints.data(),  //Pontos
                vecReservoirPoints.size()   //Quantidade de pontos
    );

    //Junction
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    painter.drawEllipse (windowToViewPort(this->junction),
                         this->junctionRadius,
                         this->junctionRadius);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(event->rect(), this->pixmap);
}

bool MainWindow::checkClickInElement(QPointF clickViewPortPosition)
{
    //Deve checar click em algum dos elementos
    //O algoritmo do click pode estar considerando outra orientação, checar

    QPointF clickWindowPosition = viewPortToWindow(clickViewPortPosition);

    //Check demand
    //Obtem pontos da demanda em window
    std::vector<QPointF> vecDemandPoints = getVectorAsWindowPoints
    (
        getDemandPoints(windowToViewPort(this->demand), this->demandRadius)
    );

    //Check demand
    if (pnpoly(vecDemandPoints.size(), vecDemandPoints, clickWindowPosition))
    {
        cout << "The demand was clicked !!!" << endl << endl;
        return true;
    }

    //Check reservoir
    //Obtem pontos do reservoir em window
    std::vector<QPointF> vecReservoirPoints = getVectorAsWindowPoints
    (
        getReservoirPoints(windowToViewPort(this->reservoir), this->reservoirRadius)
    );

    if (pnpoly(vecReservoirPoints.size(), vecReservoirPoints, clickWindowPosition))
    {
        cout << "The reservoir was clicked !!!" << endl << endl;
        return true;
    }

    //Check juction
    //Checagem é diferente. Usa distância ao centro. Pode ser feita com viewportPositions
    if(pointIsInsideCircle(windowToViewPort(this->junction), this->junctionRadius, clickViewPortPosition))
    {
        cout << "The junction was clicked !!!" << endl << endl;
        return true;
    }


    cout << "No element was clicked !!!" << endl << endl;
    return false;
}

/*PNPOLY - Point Inclusion in Polygon Test
W. Randolph Franklin (WRF)
https://web.archive.org/web/20161108113341/https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
*/
bool MainWindow::pnpoly(int nVert, const std::vector<QPointF>& vert, const QPointF& point)
{
  bool c = 0;
  for (int i = 0, j = nVert-1; i < nVert; j = i++)
  {
    if ( ((vert[i].y() > point.y()) != (vert[j].y()>point.y())) &&
     (point.x() < (vert[j].x()-vert[i].x()) * (point.y()-vert[i].y()) / (vert[j].y()-vert[i].y()) + vert[i].x()) )
       c = !c;
  }
  return c;
}

double MainWindow::distBetweenTwoPoints(const QPointF& pointA, const QPointF& pointB)
{
    return sqrt(pow(pointA.x()-pointB.x(), 2) + pow(pointA.y()-pointB.y(), 2));
}

bool MainWindow::pointIsInsideCircle(const QPointF& center, double radius, const QPointF& point)
{
    double distance = distBetweenTwoPoints(center, point);
    return distance <= radius;
}
