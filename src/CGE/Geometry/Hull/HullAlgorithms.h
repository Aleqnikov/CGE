#ifndef HULL_ALGORITHMS_H
#define HULL_ALGORITHMS_H

#include "../../Algebra/Point2D.h"
#include "../../Algebra/LinealAlgebra.h"


namespace HullAlgorithms {

    std::vector<Point2D> JarvisMarch (std::vector<Point2D>::const_iterator,
                std::vector<Point2D>::const_iterator);

    std::vector<Point2D> Andrews (std::vector<Point2D>::const_iterator,
                std::vector<Point2D>::const_iterator);

}


#endif // HULL_ALGORITHMS_H
