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
bool LinealAlgebra::cross_rib(Point2D a, Point2D b, Point2D p) {
    if(a.y > b.y) std::swap(a, b);

    if(p.y <= a.y || p.y > b.y) return false;

    // orientation(a, b, far) → где точка «далеко справа» относительно того же ребра.
    // Если результаты разные, луч пересекает ребро.
    Point2D far = {1e9, p.y};

    Orientations o1 = orientation(a, b, p);
    Orientations o2 = orientation(a, b, far);

    return o1 != o2;
}
