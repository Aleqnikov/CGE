#ifndef REGULAR_POLUGON_H
#define REGULAR_POLUGON_H

#include "Polygon.h"
class RegularPolygon : public Polygon{
public:
    RegularPolygon(int, InPolygonChecker);
    RegularPolygon();

    void  Regenerate() override;

    bool inPolygon(Point2D point) override{
        return checker_func_(point, Point2D(0,0) , vertices.begin(), vertices.end());
    }
};

#endif //REGULAR_POLUGON_H
