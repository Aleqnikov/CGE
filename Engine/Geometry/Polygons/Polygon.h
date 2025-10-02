//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <algorithm>

#include "../../Algebra/Point2D.h"
#include "../../Algebra/LinealAlgebra.h"

/**
 * @brief Виртуальный класс многоугольника, является предком всех
 * остальных классов многоугольника.
 */
class Polygon {
public:

    std::vector<Point2D> vertices;
    bool virtual inPolygon(Point2D) { return false; }

    void virtual Regenerate() {};
};


#endif //SHAPE_H
