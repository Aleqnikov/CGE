//
// Created by Иван Алейников on 19.09.2025.
//

#ifndef STARPOLYGON_H
#define STARPOLYGON_H

#include "Polygon.h"
#include "../../Algebra/LinealAlgebra.h"

class StarPolygon : public Polygon{
public:
    StarPolygon(int count_vert);
    
    StarPolygon() : StarPolygon(10) {} ;

    bool inPolygon(Point2D point) override;

    void  Regenerate() override;
};





#endif //STARPOLYGON_H
