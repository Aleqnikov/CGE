//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef REGULARPOLUGON_H
#define REGULARPOLUGON_H

#include "Polygon.h"

class RegularPolygon : public Polygon{
public:
    RegularPolygon();

    bool inPolygon(Point2D point);


};



#endif //REGULARPOLUGON_H
