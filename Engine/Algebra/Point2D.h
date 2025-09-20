//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef POINT2D_H
#define POINT2D_H



class Point2D {
public:
    double x, y;


    Point2D(double x, double y) : x(x), y(y) {};
    Point2D() : x(0), y(0) {};
    
    Point2D operator+(const Point2D &p) const {return Point2D(x+p.x, y+p.y);};
    Point2D operator-(const Point2D &p) const {return Point2D(x-p.x, y-p.y);};

};



#endif //POINT2D_H
