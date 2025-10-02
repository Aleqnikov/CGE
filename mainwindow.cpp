#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./Engine/Geometry/Polygons/Polygon.h"
#include "./Engine/Geometry/Polygons/ConvexPolygon.h"
#include "./Engine/Geometry/Polygons/RegularPolygon.h"
#include "./Engine/Geometry/Polygons/StarPolygon.h".h"

#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QVBoxLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаём QStackedWidget и делаем его центральным виджетом
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Создаём первую страницу
    FirstPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::FirstPage()
{
    QWidget *container = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(container);

    QPushButton *dot_in_polygon = new QPushButton("Определение нахождения точки внутри многоугольника");
    QPushButton *create_convex_hull = new QPushButton("Построение выпуклой оболочки.");

    layout->addWidget(dot_in_polygon);
    layout->addWidget(create_convex_hull);

    container->setLayout(layout);
    stackedWidget->addWidget(container);

    connect(dot_in_polygon, &QPushButton::clicked, [this]() {
        GetDataInPolygon();
        stackedWidget->setCurrentIndex(1);
    });
}

void MainWindow::GetDataInPolygon()
{
    QWidget *page = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(page);

    QLabel *count_peacs = new QLabel("Введите количество вершин многоугольника");
    QSpinBox *spin = new QSpinBox;
    spin->setRange(3, 10000);
    spin->setValue(10);

    QLabel *mode_of_polygon = new QLabel("Выберите вид многоугольника.");
    QComboBox *setModStat = new QComboBox;
    setModStat->addItems({"convex", "star", "ordinary"});

    QPushButton *confirm = new QPushButton("Подтвердить");

    connect(confirm, &QPushButton::clicked, [this, spin, setModStat]() {
        int n = spin->value();

        std::shared_ptr<Polygon> polygon;

        if(setModStat->currentText() == "convex")
            polygon = std::make_shared<ConvexPolygon>(n);

        if(setModStat->currentText() == "star")
            polygon = std::make_shared<StarPolygon>(n);

        if(setModStat->currentText() == "ordinary")
            polygon = std::make_shared<RegularPolygon>(n);

        PolygonInModeDraw(polygon);

    });

    mainLayout->addWidget(count_peacs);
    mainLayout->addWidget(spin);
    mainLayout->addWidget(mode_of_polygon);
    mainLayout->addWidget(setModStat);
    mainLayout->addWidget(confirm);

    page->setLayout(mainLayout);
    stackedWidget->addWidget(page);
}

void MainWindow::PolygonInModeDraw(std::shared_ptr<Polygon> polygon){
    // Преобразуем в QPolygonF
    QPolygonF qpoly;
    qpoly.reserve(polygon->vertices.size()); // резервируем память
    for (const auto &v : polygon->vertices) {
        qpoly << QPointF(v.x, v.y);
    }

    // Создаём сцену и view
    QGraphicsScene *scene = new QGraphicsScene(this);
    MyGraphicsView *view = new MyGraphicsView(polygon);
    view->setFocusPolicy(Qt::StrongFocus);
    view->setSceneAndInit(scene);

    // Фон
    scene->setBackgroundBrush(QBrush(Qt::black));

    // КРИТИЧНО: используем cosmetic pen (не масштабируется)
    QPen pen(Qt::green);
    pen.setWidth(0); // cosmetic pen - всегда 1 пиксель
    pen.setCosmetic(true);

    QGraphicsPolygonItem *polyItem = scene->addPolygon(qpoly, pen, QBrush());


    polyItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    polyItem->setFlag(QGraphicsItem::ItemIsMovable, false);

    polyItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    QWidget *graphicsPage = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(graphicsPage);
    layout->addWidget(view);
    graphicsPage->setLayout(layout);

    stackedWidget->addWidget(graphicsPage);
    stackedWidget->setCurrentIndex(2);

    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
