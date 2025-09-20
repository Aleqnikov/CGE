//
// Created by Иван Алейников on 20.09.2025.
//

#include <iostream>


#include "Point2D.h"

namespace LinealAlgebra {


    enum class Orientations{
    Left, Right, Collinear
    };

    /**
     * @brief Функция псевдо скалярного произведения.
     */
    double pscalar(Point2D a, Point2D b) {
        return a.x * b.y - a.y * b.x;
    }

    
    Orientations orientation(Point2D, Point2D, Point2D);

    
    bool cross_rib(Point2D , Point2D , Point2D );
}