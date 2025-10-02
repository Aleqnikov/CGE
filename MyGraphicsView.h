#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <memory>
#include "./Engine/Geometry/Polygons/Polygon.h"

class MyGraphicsView : public QGraphicsView {
    Q_OBJECT
private:
    std::shared_ptr<Polygon> polygon_;
    QPointF lastMouseScenePos;

    // Кэширование результата проверки
    bool lastCheckResult = false;
    bool hasCachedResult = false;

public:
    explicit MyGraphicsView(std::shared_ptr<Polygon> polygon, QWidget *parent = nullptr)
        : QGraphicsView(parent), polygon_(polygon)
    {
        setDragMode(QGraphicsView::RubberBandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setMouseTracking(true);

        // КРИТИЧНО: отключаем антиалиасинг для больших объектов
        setRenderHint(QPainter::Antialiasing, false);

        // Включаем оптимизацию рендеринга
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);

        // Кэширование фона
        setCacheMode(QGraphicsView::CacheBackground);
    }

    void setSceneAndInit(QGraphicsScene *scene) {
        setScene(scene);
        scene->setBackgroundBrush(QBrush(Qt::gray));

        // Оптимизация индексации сцены для больших объектов
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    }

protected:
    void wheelEvent(QWheelEvent *event) override {
        const double scaleFactor = 1.15;

        // Ограничиваем максимальный зум
        qreal currentScale = transform().m11();

        if (event->angleDelta().y() > 0) {
            if (currentScale < 100.0) { // макс зум
                scale(scaleFactor, scaleFactor);
            }
        } else {
            if (currentScale > 0.01) { // мин зум
                scale(1.0 / scaleFactor, 1.0 / scaleFactor);
            }
        }

        // Включаем/выключаем антиалиасинг в зависимости от зума
        updateRenderHints();
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
        updateRenderHints();
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        lastMouseScenePos = mapToScene(event->pos());

        if (polygon_) {
            lastCheckResult = polygon_->inPolygon(Point2D(lastMouseScenePos.x(), lastMouseScenePos.y()));
            hasCachedResult = true;
        }

        viewport()->update();

        QGraphicsView::mouseMoveEvent(event);
    }

    void paintEvent(QPaintEvent *event) override {
        QGraphicsView::paintEvent(event);

        if (hasCachedResult && !lastMouseScenePos.isNull()) {
            QPainter painter(viewport());

            QPoint cursorPos = mapFromScene(lastMouseScenePos);

            // Размеры текста
            QFont font = painter.font();
            font.setPointSizeF(16);
            font.setBold(true);
            painter.setFont(font);

            QString text = lastCheckResult ? "TRUE" : "FALSE";
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(text);
            int textHeight = metrics.height();

            int offsetX = -textWidth / 2;
            int offsetY = -textHeight - 10;

            QPoint textPos = cursorPos + QPoint(offsetX, offsetY);

            // Полупрозрачный фон для читаемости
            QRect bgRect(textPos.x() - 5, textPos.y() - textHeight + 5,
                         textWidth + 10, textHeight + 5);
            painter.fillRect(bgRect, QColor(0, 0, 0, 180));


            if (lastCheckResult) {
                painter.setPen(QColor(0, 255, 0));
            } else {
                painter.setPen(QColor(255, 100, 100));
            }

            painter.drawText(textPos, text);
        }
    }

    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Space) {


            polygon_->Regenerate();

            // QPolygonF для сцены
            QPolygonF qpoly;
            for (const auto &v : polygon_->vertices)
                qpoly << QPointF(v.x, v.y);

            // перерисовка сцены
            scene()->clear();

            // КРИТИЧНО: используем cosmetic pen (не масштабируется)
            QPen pen(Qt::green);
            pen.setWidth(0); // cosmetic pen - всегда 1 пиксель
            pen.setCosmetic(true);

            scene()->addPolygon(qpoly, pen);

            return;

            QGraphicsView::keyPressEvent(event);
        }
    }

private:
    // Адаптивное включение антиалиасинга
    void updateRenderHints() {
        qreal scale = transform().m11();

        // Антиалиасинг только при малом зуме
        if (scale < 5.0) {
            setRenderHint(QPainter::Antialiasing, true);
        } else {
            setRenderHint(QPainter::Antialiasing, false);
        }
    }
};

#endif // MYGRAPHICSVIEW_H
