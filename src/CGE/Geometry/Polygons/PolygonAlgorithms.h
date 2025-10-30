#ifndef POLYGON_ALGORITHMS_H
#define POLYGON_ALGORITHMS_H

#include "../../Algebra/Point2D.h"
#include "../../Algebra/LinealAlgebra.h"


namespace PolygonAlgorithms {


    int findSector(Point2D, 
                    Point2D,
                    std::vector<Point2D>::const_iterator, 
                    std::vector<Point2D>::const_iterator );

    bool pointInStarPolygon (Point2D,
                    Point2D,
                    std::vector<Point2D>::const_iterator,
                    std::vector<Point2D>::const_iterator);


    bool pointInRegularPolygon (Point2D,
                    Point2D,
                    std::vector<Point2D>::const_iterator,
                    std::vector<Point2D>::const_iterator);

}


#endif // POLYGON_ALGORITHMS_H
