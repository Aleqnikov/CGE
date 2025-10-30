#ifndef MYGRAPHICSVIEWHULL_H
#define MYGRAPHICSVIEWHULL_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QWheelEvent>
#include <memory>
#include "./src/CGE/Geometry/Hull/Hull.h"

class MyGraphicsViewHull : public QGraphicsView {
    Q_OBJECT

public:
    explicit MyGraphicsViewHull(std::shared_ptr<Hull> hull, QWidget *parent = nullptr)
        : QGraphicsView(parent), hull_(std::move(hull)), isPanning_(false), spacePressed_(false)
    {
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setMouseTracking(true);
        setRenderHint(QPainter::Antialiasing, false);
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
        setCacheMode(QGraphicsView::CacheBackground);

        // Изначально — резиновая рамка
        setDragMode(QGraphicsView::RubberBandDrag);
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
            if (currentScale < 100.0)
                scale(scaleFactor, scaleFactor);
        } else {
            if (currentScale > 0.01)
                scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
        updateRenderHints();
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (spacePressed_ && event->button() == Qt::LeftButton) {
            isPanning_ = true;
            lastPanPoint_ = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }

        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isPanning_) {
            QPointF delta = mapToScene(event->pos()) - mapToScene(lastPanPoint_);
            // Инвертируем, чтобы тянуть сцену в нужную сторону
            translate(delta.x(), delta.y());
            lastPanPoint_ = event->pos();
            event->accept();
            return;
        }

        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (isPanning_ && event->button() == Qt::LeftButton) {
            isPanning_ = false;
            setCursor(Qt::ArrowCursor);
            event->accept();
            return;
        }

        // Обработка выделения рамкой
        if (dragMode() == QGraphicsView::RubberBandDrag) {
            QRect rubberRect = rubberBandRect();
            if (!rubberRect.isEmpty()) {
                fitInView(mapToScene(rubberRect).boundingRect(), Qt::KeepAspectRatio);
            }
        }

        QGraphicsView::mouseReleaseEvent(event);
        updateRenderHints();
    }

    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
            spacePressed_ = true;
            if (!isPanning_) {
                setCursor(Qt::OpenHandCursor);
            }
            event->accept();
            return;
        }

        if (event->key() == Qt::Key_Space && hull_) {
            hull_->Regenerate();
            redrawHull();
        }

        QGraphicsView::keyPressEvent(event);
    }

    void keyReleaseEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
            spacePressed_ = false;
            if (!isPanning_) {
                setCursor(Qt::ArrowCursor);
            }
            event->accept();
            return;
        }

        QGraphicsView::keyReleaseEvent(event);
    }

private:
    void updateRenderHints() {
        qreal scale = transform().m11();
        setRenderHint(QPainter::Antialiasing, scale < 5.0);
    }

    void redrawHull() {
        if (!scene() || !hull_) return;

        scene()->clear();
        scene()->setBackgroundBrush(QBrush(Qt::gray));

        // Все точки
        const auto &allPoints = hull_->GetAllPoints();
        for (const auto &p : allPoints) {
            scene()->addEllipse(p.x_ - 1, p.y_ - 1, 2, 2,
                                Qt::NoPen, QBrush(Qt::red));
        }

        // Выпуклая оболочка
        const auto &hullPoints = hull_->GetHull();
        if (!hullPoints.empty()) {
            QPolygonF qpoly;
            for (const auto &p : hullPoints)
                qpoly << QPointF(p.x_, p.y_);

            QPen hullPen(Qt::green);
            hullPen.setWidth(0);
            hullPen.setCosmetic(true);
            scene()->addPolygon(qpoly, hullPen);
        }
    }

    std::shared_ptr<Hull> hull_;

    // Панорамирование
    bool isPanning_ = false;
    bool spacePressed_ = false;
    QPoint lastPanPoint_;
};

#endif // MYGRAPHICSVIEWHULL_H