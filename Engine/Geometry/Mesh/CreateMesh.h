#ifndef CREATEMESH_H
#define CREATEMESH_H

#include "../../Algebra/Point2D.h"
#include "../../Algebra/LinealAlgebra.h"

class Mesh{
public:
    Mesh();
    Mesh(int);

    std::vector<Point2D> JarvisMarch();
    std::vector<Point2D> Andrews() {return std::vector<Point2D>();};
    std::vector<Point2D> Implemential() {return std::vector<Point2D>();};


    std::vector<Point2D> mesh;
};


#endif //CREATEMESH_H
