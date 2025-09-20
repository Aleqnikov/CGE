//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef STARPOLYGON_H
#define STARPOLYGON_H

#include "Polygon.h"

class StarPolygon : public Polygon{
public:
    StarPolygon(int count_vert);
    
    StarPolygon() : StarPolygon(10) {} ;

    bool inPolygon(Point2D point);
    int find_sector(Point2D point);
};



#endif //STARPOLYGON_H
