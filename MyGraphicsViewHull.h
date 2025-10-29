#ifndef MYGRAPHICSVIEWHULL_H
#define MYGRAPHICSVIEWHULL_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <memory>
#include "./src/CGE/Geometry/Hull/Hull.h"

class MyGraphicsViewHull : public QGraphicsView {
    Q_OBJECT
public:
    explicit MyGraphicsViewHull(std::shared_ptr<Hull> hull, QWidget *parent = nullptr)
        : QGraphicsView(parent), hull_(std::move(hull))
    {
        setDragMode(QGraphicsView::RubberBandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setMouseTracking(true);
        setRenderHint(QPainter::Antialiasing, false);
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
        setCacheMode(QGraphicsView::CacheBackground);
    }

    void setSceneAndInit(QGraphicsScene *scene) {
        setScene(scene);
        if (scene) {
            scene->setBackgroundBrush(QBrush(Qt::gray));
            scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        }

        redrawHull();
    }

protected:
    void wheelEvent(QWheelEvent *event) override {
        const double scaleFactor = 1.15;
        qreal currentScale = transform().m11();

        if (event->angleDelta().y() > 0) {
            if (currentScale < 100.0) scale(scaleFactor, scaleFactor);
        } else {
            if (currentScale > 0.01) scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
        updateRenderHints();
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            setDragMode(QGraphicsView::ScrollHandDrag);
            QGraphicsView::mousePressEvent(event);
            setDragMode(QGraphicsView::RubberBandDrag);
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (dragMode() == QGraphicsView::RubberBandDrag) {
            QRect rect = rubberBandRect();
            if (!rect.isEmpty())
                fitInView(mapToScene(rect).boundingRect(), Qt::KeepAspectRatio);
        }
        QGraphicsView::mouseReleaseEvent(event);
        updateRenderHints();
    }

    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Space) {
            if (hull_) {
                hull_->Regenerate();
                redrawHull();
            }
            QGraphicsView::keyPressEvent(event);
            return;
        }
        QGraphicsView::keyPressEvent(event);
    }

private:
    void updateRenderHints() {
        qreal scale = transform().m11();
        setRenderHint(QPainter::Antialiasing, scale < 5.0);
    }

    void redrawHull() {
        if (!scene() || !hull_) return;

        scene()->clear();

        const auto &points = hull_->GetHull();
        if (points.empty()) return;

        QPolygonF qpoly;
        qpoly.reserve(points.size());
        for (const auto &p : points)
            qpoly << QPointF(p.x_, p.y_);

        QPen pen(Qt::green);
        pen.setWidth(0);
        pen.setCosmetic(true);
        scene()->addPolygon(qpoly, pen);

        const auto &src = hull_->GetHull();
        for (const auto &p : src) {
            scene()->addEllipse(p.x_ - 1.5, p.y_ - 1.5, 3, 3, QPen(Qt::black), QBrush(Qt::red));
        }
    }

    std::shared_ptr<Hull> hull_;
};

#endif // MYGRAPHICSVIEWHULL_H
