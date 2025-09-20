//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef REGULARPOLUGON_H
#define REGULARPOLUGON_H

#include "Polygon.h"


/**
 * @brief Класс реализующий  многоугольник.
 * 
 * Есть метод который определяет, принадлежит ли передаваемая точка 
 * текущему многоугольнику.
 */
class RegularPolygon : public Polygon{
public:
    RegularPolygon(int count_vert);
    
    RegularPolygon() : RegularPolygon(10) {} ;

    bool inPolygon(Point2D point);
};

#endif //REGULARPOLUGON_H
