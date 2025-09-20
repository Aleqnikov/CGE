//
// Created by Иван Алейников on 19.09.2025.
//

#include "LinealAlgebra.h"

double LinealAlgebra::pscalar(Point2D a, Point2D b) {
    return a.x * b.y - a.y * b.x;
}


/**
 * @breif Поиск ориентации точки с относительно точек а и b
*/
LinealAlgebra::Orientations LinealAlgebra::orientation(Point2D a, Point2D b, Point2D c) {
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
bool LinealAlgebra::cross_rib(Point2D b, Point2D t, Point2D z) {
    if(!(std::min(b.y, t.y) < z.y && std::max(b.y, t.y) <= z.y)) 
        return false;

    if(orientation(b, t, z) != Orientations::Right)
        return false;

    return true;
}
