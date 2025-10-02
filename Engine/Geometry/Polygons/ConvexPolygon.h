//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include "Polygon.h"


/**
 * @brief Класс реализующий выпуклый многоугольник.
 * 
 * В нем представленна реализация метода поиска сектора, которому принадлежит 
 * точка. 
 * А также метод, который определяет, принадлежит ли передаваемая точка 
 * текущему многоугольнику.
 */
class ConvexPolygon : public Polygon{
public:
    ConvexPolygon(int);
    ConvexPolygon() : ConvexPolygon(10) {};

    bool inPolygon(Point2D point) override;
    int find_sector(Point2D point);
     void  Regenerate() override;
};



#endif //CONVEXPOLYGON_H
