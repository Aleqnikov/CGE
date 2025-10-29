#ifndef LINEAL_ALGEBRA_H
#define LINEAL_ALGEBRA_H

#include <iostream>

#include "Point2D.h"


namespace LinealAlgebra {

    enum class Orientations {
        Left,
        Right,
        Colinear
    };

    double pscalar(Point2D, Point2D);

    Orientations orientation(Point2D, Point2D, Point2D);

    bool cross_rib(Point2D, Point2D, Point2D);

    double distance(const Point2D& a, const Point2D& b);

}


#endif // LINEAL_ALGEBRA_H