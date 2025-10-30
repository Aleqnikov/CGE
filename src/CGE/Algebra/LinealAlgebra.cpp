#include "LinealAlgebra.h"

namespace LinAl = LinealAlgebra;


double LinealAlgebra::pscalar(Point2D a, Point2D b) {
    return a.x_ * b.y_ - a.y_ * b.x_; // pseudoscalar(a, b) = ax*by - ay*bx
}

LinealAlgebra::Orientations LinealAlgebra::orientation(Point2D a, Point2D b, Point2D c) {
    double ps_res = pscalar(a - b, c - b); // pseudoscalar(ab, ac)

    if(ps_res > 0) return Orientations::Left;      // left orientation
    else if(ps_res < 0) return Orientations::Right; // right orientation
    return Orientations::Colinear;                  // collinear
}

// Проверка пересечения луча с ребром для точки в простом многоугольнике
bool LinealAlgebra::cross_rib(Point2D a, Point2D b, Point2D p) {
    if(a.y_ > b.y_) std::swap(a, b);

    // Учитываем пересечение если by < zy ≤ ty
    if(p.y_ <= a.y_ || p.y_ > b.y_) return false;

    // и orientation(b, t, z) = right
    Orientations o1 = orientation(a, b, p);
    return o1 == Orientations::Right;
}

double LinAl::distance(const Point2D& a, const Point2D& b) {
    double dx = a.x_ - b.x_;
    double dy = a.y_ - b.y_;
    return dx * dx + dy * dy;
}