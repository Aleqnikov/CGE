//
// Created by Иван Алейников on 19.09.2025.
//

#include "ConvexPolygon.h"

/**
 * partition_point — это функция которая находит первый элемент в отсортированном диапазоне, не удовлетворяющий заданному условию 
 */
int ConvexPolygon::find_sector(Point2D point){
    Point2D base = vertices[0];

    auto it = std::partition_point(vertices.begin() + 1, vertices.end(),
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - base, point - base) >= 0;
        }
    );

    return static_cast<int>(std::distance(vertices.begin(), it)) - 1;
}


bool ConvexPolygon::inPolygon(Point2D point){
    int left = find_sector(point);
    int right = (left == vertices.size() - 1)? 0 : left + 1;
    

    if(LinealAlgebra::orientation(vertices[left], vertices[right], point) == LinealAlgebra::Orientations::Right)
        return true;

    return false;
}