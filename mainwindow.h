#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <memory>

#include "./src/CGE/Geometry/Polygons/Polygon.h"
#include "MyGraphicsView.h"
#include "MyGraphicsViewHull.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private:
    enum class Page {
        First = 0,
        Input = 1,
        Graphics = 2
    };

    void createFirstPage();
    void showPolygonInputPage();
    void showConvexHullInputPage();

    void drawPolygonMode(std::shared_ptr<Polygon> polygon);
    void drawHull(const std::vector<Point2D> &points, const std::vector<Point2D> &hull);

    // stacked widget для переключения страниц
    QStackedWidget *stackedWidget = nullptr;
};

#endif // MAINWINDOW_H
