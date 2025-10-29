#include "Point2D.h"




Point2D::Point2D(double x, double y) : x_(x), y_(y) {};

Point2D::Point2D() : Point2D(0, 0) {};

Point2D Point2D::operator+(const Point2D& point) const {
    return Point2D(x_ + point.x_, y_ + point.y_);
}

Point2D Point2D::operator-(const Point2D& point) const {
    return Point2D(x_ - point.x_, y_ - point.y_);
}

bool Point2D::operator!=(const Point2D& point) const {
    return !(*this == point);
}



bool Point2D::operator==(const Point2D& p) const {
    return x_ == p.x_ && y_ == p.y_;
}

bool Point2D::operator<(const Point2D& p) const {
    return (x_ < p.x_) || (x_ == p.x_ && y_ < p.y_);
}