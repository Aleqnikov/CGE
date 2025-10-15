#ifndef MYGRAPHICSVIEW_SCALABLE_H
#define MYGRAPHICSVIEW_SCALABLE_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPainter>

class MyGraphicsViewHull : public QGraphicsView {
    Q_OBJECT

public:
    explicit MyGraphicsViewHull(QWidget *parent = nullptr)
        : QGraphicsView(parent)
    {
        setDragMode(QGraphicsView::RubberBandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setMouseTracking(true);

        // Антиалиасинг для всех объектов, масштабируется
        setRenderHint(QPainter::Antialiasing, true);

        // Оптимизация рендеринга
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
    }

    void setSceneAndInit(QGraphicsScene *scene) {
        setScene(scene);
        scene->setBackgroundBrush(QBrush(Qt::gray));
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    }

protected:
    void wheelEvent(QWheelEvent *event) override {
        const double scaleFactor = 1.15;
        if (event->angleDelta().y() > 0) {
            scale(scaleFactor, scaleFactor);
        } else {
            scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        }
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::RightButton) {
            setDragMode(QGraphicsView::ScrollHandDrag);
            QGraphicsView::mousePressEvent(event);
            setDragMode(QGraphicsView::RubberBandDrag);
        } else {
            QGraphicsView::mousePressEvent(event);
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (dragMode() == QGraphicsView::RubberBandDrag) {
            QRect rubberRect = rubberBandRect();
            if (!rubberRect.isEmpty())
                fitInView(mapToScene(rubberRect).boundingRect(), Qt::KeepAspectRatio);
        }
        QGraphicsView::mouseReleaseEvent(event);
    }
};

#endif // MYGRAPHICSVIEW_SCALABLE_H
