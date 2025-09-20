//
// Created by Иван Алейников on 19.09.2025.
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
        return a.x * b.x - a.y * b.y;
    }

    /**
     * @breif Поиск ориентации точки с относительно точек а и b
     */
    Orientations orientation(Point2D a, Point2D b, Point2D c) {
        double ps_res = pscalar( a - b, c - b);

        if( ps_res > 0 )
            return Orientations::Left;
        else if( ps_res < 0 )
            return Orientations::Right;

        return Orientations::Collinear;
    }

    /**
     * @brief Данная функция проверяет, пересекает прямая, проведеная из z ребро, задаю
     * задающееся точками b, t
     */
    bool cross_rib(Point2D b, Point2D t, Point2D z) {
        if(!(std::min(b.y, t.y) < z.y && std::max(b.y, t.y) <= z.y)) 
            return false;

        if(orientation(b, t, z) != Orientations::Right)
            return false;

        return true;
    }





}