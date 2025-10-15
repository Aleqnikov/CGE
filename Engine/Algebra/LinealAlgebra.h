//
// Created by Иван Алейников on 20.09.2025.
//

#ifndef LINEAL_ALGEBRA_H
#define LINEAL_ALGEBRA_H

#include <iostream>


#include "Point2D.h"



namespace LinealAlgebra {

    enum class Orientations{
        Left, Right, Collinear
    };


    /**
     * @brief Функция псевдо скалярного произведения.
     */
    double pscalar(Point2D, Point2D);
    
    Orientations orientation(Point2D, Point2D, Point2D);

    
    bool cross_rib(Point2D , Point2D , Point2D );
    
    bool PointInConvexPolygon(std::vector<Point2D>::const_iterator, 
                            std::vector<Point2D>::const_iterator, 
                            Point2D);
    int FindSector(Point2D, 
                    std::vector<Point2D>::const_iterator, 
                    std::vector<Point2D>::const_iterator);
}


#endif // LINEAL_ALGEBRA_H
