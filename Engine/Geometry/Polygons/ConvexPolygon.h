//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include "Polygon.h"

class ConvexPolygon : public Polygon{
public:
    ConvexPolygon();


    bool inPolygon(Point2D point);
    int find_sector(Point2D point);
};



#endif //CONVEXPOLYGON_H
