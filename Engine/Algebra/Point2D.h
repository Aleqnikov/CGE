//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef POINT2D_H
#define POINT2D_H



class Point2D {
public:
    double x, y;

    Point2D();
    Point2D(double x, double y);
    
    Point2D operator+(const Point2D &p) const;
    Point2D operator-(const Point2D &p) const;



};



#endif //POINT2D_H
