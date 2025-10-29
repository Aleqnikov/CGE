#ifndef POINT2D_H
#define POINT2D_H

struct Point2D
{
    double x_, y_;


    Point2D();
    Point2D(double, double);

    Point2D operator+(const Point2D& p) const;
    Point2D operator-(const Point2D& p) const;
    bool operator==(const Point2D& p) const;
    bool operator!=(const Point2D& p) const;
    bool operator<(const Point2D& p) const;
};



#endif // POINT2D_H