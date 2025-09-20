//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <algorithm>

#include "../../Algebra/Point2D.h"
#include "../../Algebra/LinealAlgebra.h"


class Polygon {
public:
    std::vector<Point2D> vertices;
    virtual bool inPolygon(Point2D point);
};



#endif //SHAPE_H
