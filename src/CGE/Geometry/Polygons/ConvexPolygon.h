#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include "Polygon.h"

class ConvexPolygon : public Polygon{
public:
    ConvexPolygon(int, InPolygonChecker);
    ConvexPolygon();

    void  Regenerate() override;
};


#endif //CONVEX_POLYGON_H