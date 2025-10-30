#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include "Polygon.h"

class ConvexPolygon : public Polygon{
public:
    ConvexPolygon(int, InPolygonChecker);
    ConvexPolygon();

    void  Regenerate() override;

    bool inPolygon(Point2D point) {
        return checker_func_(point, vertices[0],  vertices.begin(), vertices.end());
    }
};


#endif //CONVEX_POLYGON_H
