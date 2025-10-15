#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>

#include "MyGraphicsView.h"
#include "MyGraphicsViewHull.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void FirstPage();
    void GetDataInPolygon();
    void PolygonInModeDraw(std::shared_ptr<Polygon>);
    void GetDataConvexHull();
    void HullDraw(std::vector<Point2D>, std::vector<Point2D>);

private:
    QStackedWidget *stackedWidget;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
