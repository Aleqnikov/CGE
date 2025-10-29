#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>


#include "./src/CGE/Geometry/Polygons/Polygon.h"
#include "./src/CGE/Geometry/Polygons/PolygonAlgorithms.h"
#include "./src/CGE/Geometry/Polygons/ConvexPolygon.h"
#include "./src/CGE/Geometry/Polygons/RegularPolygon.h"
#include "./src/CGE/Geometry/Polygons/StarPolygon.h"
#include "./src/CGE/Geometry/Hull/Hull.h"
#include "./src/CGE/Geometry/Hull/HullAlgorithms.h"

#include "MyGraphicsView.h"
#include "MyGraphicsViewHull.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    createFirstPage();
}

void MainWindow::createFirstPage()
{
    // container будет дочерним для stackedWidget
    QWidget *container = new QWidget(stackedWidget);
    QVBoxLayout *layout = new QVBoxLayout(container);

    auto *dotBtn = new QPushButton(tr("Определение нахождения точки внутри многоугольника"), container);
    auto *hullBtn = new QPushButton(tr("Построение выпуклой оболочки."), container);

    layout->addWidget(dotBtn);
    layout->addWidget(hullBtn);
    container->setLayout(layout);

    stackedWidget->addWidget(container); // индекс Page::First

    // Лямбда-обработчики, не меняющие логику
    connect(dotBtn, &QPushButton::clicked, this, [this]() {
        showPolygonInputPage();
        stackedWidget->setCurrentIndex(static_cast<int>(Page::Input));
    });

    connect(hullBtn, &QPushButton::clicked, this, [this]() {
        showConvexHullInputPage();
        stackedWidget->setCurrentIndex(static_cast<int>(Page::Input));
    });
}

void MainWindow::showConvexHullInputPage()
{
    QWidget *page = new QWidget(stackedWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(page);

    QLabel *countLabel = new QLabel(tr("Введите количество точек для построения выпуклой оболочки"), page);
    QSpinBox *spin = new QSpinBox(page);
    spin->setRange(10, 10000);
    spin->setValue(100);

    QLabel *modeLabel = new QLabel(tr("Выберите алгоритм построения выпуклой оболочки"), page);
    QComboBox *combo = new QComboBox(page);
    combo->addItems({"Jarvis", "Andrews", "Implemential"});

    QPushButton *confirm = new QPushButton(tr("Подтвердить"), page);

    mainLayout->addWidget(countLabel);
    mainLayout->addWidget(spin);
    mainLayout->addWidget(modeLabel);
    mainLayout->addWidget(combo);
    mainLayout->addWidget(confirm);
    page->setLayout(mainLayout);
    stackedWidget->addWidget(page);

    connect(confirm, &QPushButton::clicked, this, [this, spin, combo]() {
        const int n = spin->value();
        std::shared_ptr<Hull> hullPtr;

        const QString choice = combo->currentText();

        // Выбираем алгоритм построения
        if (choice == "Jarvis")
            hullPtr = std::make_shared<Hull>(n, HullAlgorithms::JarvisMarch);
        else if (choice == "Andrews")
            hullPtr = std::make_shared<Hull>(n, HullAlgorithms::Andrews);
        else
            hullPtr = std::make_shared<Hull>(n, HullAlgorithms::Andrews); // default

        // Создаём сцену и виджет для отображения оболочки
        QGraphicsScene *scene = new QGraphicsScene(this);
        auto *view = new MyGraphicsViewHull(hullPtr);
        view->setSceneAndInit(scene);

        // Добавляем на страницу отображения (Page::Graphics)
        QWidget *graphicsPage = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(graphicsPage);
        layout->addWidget(view);
        graphicsPage->setLayout(layout);
        stackedWidget->addWidget(graphicsPage);

        // Переключаемся на страницу с графикой
        stackedWidget->setCurrentWidget(graphicsPage);
    });
}


void MainWindow::showPolygonInputPage()
{
    QWidget *page = new QWidget(stackedWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(page);

    QLabel *countLabel = new QLabel(tr("Введите количество вершин многоугольника"), page);
    QSpinBox *spin = new QSpinBox(page);
    spin->setRange(3, 10000);
    spin->setValue(10);

    QLabel *modeLabel = new QLabel(tr("Выберите вид многоугольника."), page);
    QComboBox *combo = new QComboBox(page);
    combo->addItems({"convex", "star", "ordinary"});

    QPushButton *confirm = new QPushButton(tr("Подтвердить"), page);

    mainLayout->addWidget(countLabel);
    mainLayout->addWidget(spin);
    mainLayout->addWidget(modeLabel);
    mainLayout->addWidget(combo);
    mainLayout->addWidget(confirm);
    page->setLayout(mainLayout);
    stackedWidget->addWidget(page);

    connect(confirm, &QPushButton::clicked, this, [this, spin, combo]() {
        const int n = spin->value();
        std::shared_ptr<Polygon> polygon;

        const QString choice = combo->currentText();
        if (choice == "convex")
            polygon = std::make_shared<ConvexPolygon>(n, PolygonAlgorithms::pointInStarPolygon);
        else if (choice == "star")
            polygon = std::make_shared<StarPolygon>(n, PolygonAlgorithms::pointInStarPolygon2);
        else
            polygon = std::make_shared<RegularPolygon>(n, PolygonAlgorithms::pointInRegularPolygon);

        drawPolygonMode(polygon);
        stackedWidget->setCurrentIndex(static_cast<int>(Page::Graphics));
    });
}

void MainWindow::drawPolygonMode(std::shared_ptr<Polygon> polygon)
{
    // Преобразуем в QPolygonF
    QPolygonF qpoly;
    qpoly.reserve(polygon->vertices.size());
    for (const auto &v : polygon->vertices) {
        qpoly << QPointF(v.x_, v.y_);
    }

    // Сцена и view
    QGraphicsScene *scene = new QGraphicsScene(this);
    MyGraphicsView *view = new MyGraphicsView(polygon, nullptr);
    view->setSceneAndInit(scene);

    scene->setBackgroundBrush(QBrush(Qt::black));

    QPen pen(Qt::green);
    pen.setWidth(0);
    pen.setCosmetic(true);

    // Рисуем сам полигон
    scene->addPolygon(qpoly, pen);

    // ==== Подписи индексов вершин ====
    QFont font;
    font.setPointSize(8);
    font.setBold(true);

    for (int i = 0; i < polygon->vertices.size(); ++i) {
        const auto &v = polygon->vertices[i];

        QGraphicsTextItem *text = scene->addText(QString::number(i), font);
        text->setDefaultTextColor(Qt::yellow);
        text->setPos(v.x_, v.y_); // без смещения!
        text->setFlag(QGraphicsItem::ItemIgnoresTransformations, true); // не масштабируется при зуме
    }
    // ==================================

    QWidget *graphicsPage = new QWidget(stackedWidget);
    QVBoxLayout *layout = new QVBoxLayout(graphicsPage);
    layout->addWidget(view);
    graphicsPage->setLayout(layout);

    stackedWidget->addWidget(graphicsPage);
    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}



void MainWindow::drawHull(const std::vector<Point2D> &points, const std::vector<Point2D> &hull)
{
    QPolygonF qpoly;
    qpoly.reserve(hull.size());
    for (const auto &v : hull) qpoly << QPointF(v.x_, v.y_);

    QGraphicsScene *scene = new QGraphicsScene(this);
    MyGraphicsViewHull *view = new MyGraphicsViewHull(nullptr);
    view->setSceneAndInit(scene);
    scene->setBackgroundBrush(QBrush(Qt::black));

    QPen greenPen(Qt::green);
    greenPen.setWidth(0);
    greenPen.setCosmetic(true);

    // Полигон оболочки (outline)
    QGraphicsPolygonItem *polyItem = scene->addPolygon(qpoly, greenPen, QBrush());
    polyItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    polyItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    polyItem->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    // Точки
    QBrush brush(Qt::red);
    QPen noPen(Qt::NoPen);
    constexpr double radius = 2.5;

    for (const auto &p : points) {
        QGraphicsEllipseItem *pt = scene->addEllipse(-radius, -radius, radius * 2, radius * 2, noPen, brush);
        pt->setPos(p.x_, p.y_);
        pt->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        pt->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    }

    QWidget *graphicsPage = new QWidget(stackedWidget);
    QVBoxLayout *layout = new QVBoxLayout(graphicsPage);
    layout->addWidget(view);
    graphicsPage->setLayout(layout);

    stackedWidget->addWidget(graphicsPage);
    view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}
