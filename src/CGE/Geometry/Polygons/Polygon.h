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

    // виртуальная функция с определением
    virtual void Regenerate() {};  

    bool inPolygon(Point2D point){
        return checker_func_(point, vertices.begin(), vertices.end());
    }

    virtual ~Polygon() = default; 

protected:
    using InPolygonChecker = std::function<bool(
        Point2D,
        std::vector<Point2D>::const_iterator,
        std::vector<Point2D>::const_iterator
    )>;
    
    InPolygonChecker checker_func_;
};

#endif //POLYGON_H
