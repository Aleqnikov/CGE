//
// Created by Иван Алейников on 19.09.2025.
//

#include "RegularPolygon.h"




bool RegularPolygon::inPolygon(Point2D point){
    int cnt = 0;

    for(int i = 0; i < vertices.size() - 1; i++)
        if(LinealAlgebra::cross_rib(vertices[i], vertices[i + 1], point))
            cnt++;
    
    return cnt % 2 == 0;
}