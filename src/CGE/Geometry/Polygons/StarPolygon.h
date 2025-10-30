#ifndef STAR_POLYGON_H
#define STAR_POLYGON_H

#include "Polygon.h"


class StarPolygon : public Polygon{
public:
    StarPolygon(int, InPolygonChecker);
    StarPolygon();

    void  Regenerate() override;

    bool inPolygon(Point2D point) {
        return checker_func_(point, Point2D(0, 0),  vertices.begin(), vertices.end());
    }
};

#endif //STAR_POLYGON_H
