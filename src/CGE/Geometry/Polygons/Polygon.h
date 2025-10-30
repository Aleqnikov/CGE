#ifndef POLYGON_H
#define POLYGON_H

#include <algorithm>
#include <cmath>
#include <functional>
#include <random>
#include <set>
#include <vector>

#include "PolygonAlgorithms.h"

class Polygon {
public:
    std::vector<Point2D> vertices;

    virtual void Regenerate() {};  

    virtual bool inPolygon(Point2D point) = 0;
    virtual ~Polygon() = default; 

protected:
    using InPolygonChecker = std::function<bool(
        Point2D,
        Point2D,
        std::vector<Point2D>::const_iterator,
        std::vector<Point2D>::const_iterator
    )>;
    
    InPolygonChecker checker_func_;
};

#endif //POLYGON_H
