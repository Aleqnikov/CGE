#ifndef STAR_POLYGON_H
#define STAR_POLYGON_H

#include "Polygon.h"


class StarPolygon : public Polygon{
public:
    StarPolygon(int, InPolygonChecker);
    StarPolygon();

    void  Regenerate() override;
};

#endif //STAR_POLYGON_H
