#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void refreshPixmap();
    bool checkClickInElement(QPointF position);
    bool pnpoly(int nVert, const std::vector<QPointF> &vert, const QPointF &point);
    double distBetweenTwoPoints(const QPointF &pointA, const QPointF &pointB);
    bool pointIsInsideCircle(const QPointF &center, double radius, const QPointF &point);
private:
    Ui::MainWindow *ui;
    QPixmap pixmap;

    QPointF demand = {0, 0}; //Informado com base em window
    QPointF reservoir = {90, 0}; //Informado com base em window
    QPointF junction = {-90, 0}; //Informado com base em window

    double demandRadius = 10;
    double reservoirRadius = 10;
    double junctionRadius = 10;
};

#endif // MAINWINDOW_H
