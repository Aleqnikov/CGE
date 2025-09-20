//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef BELONGINGPOLYGON_H
#define BELONGINGPOLYGON_H

#include <memory>

#include "../Geometry/Polygons/Polygon.h"
#include "../Geometry/Polygons/ConvexPolygon.h"
#include "../Geometry/Polygons/StarPolygon.h"
#include "../Geometry/Polygons/RegularPolygon.h"



class BelongingPolygon {
private:
    std::shared_ptr<Polygon> polygon;

public:
    BelongingPolygon(std::shared_ptr<Polygon> polygon);

    bool solve(Point2D point);

    bool inPolygon( std::shared_ptr<ConvexPolygon> ConPol, Point2D point);
    bool inPolygon( std::shared_ptr<StarPolygon> StarPol, Point2D point);
    bool inPolygon( std::shared_ptr<RegularPolygon> RegPol, Point2D point);
};



#endif //BELONGINGPOLYGON_H
