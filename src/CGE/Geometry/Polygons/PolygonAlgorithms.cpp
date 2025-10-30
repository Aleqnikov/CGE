#include "PolygonAlgorithms.h"

namespace LinAl = LinealAlgebra;

namespace PolAlg = PolygonAlgorithms;

using namespace LinAl;



bool PolAlg::pointInRegularPolygon(Point2D point,
                                    Point2D p2,
                                    std::vector<Point2D>::const_iterator start,
                                    std::vector<Point2D>::const_iterator end) {
                                
    int intersection_count = 0;
    
    int num_vertices = std::distance(start, end);

    for (int i = 0; i < num_vertices; ++i) {
        const Point2D& vertex_a = start[i];
        
        const Point2D& vertex_b = start[(i + 1) % num_vertices];

        if (LinAl::cross_rib(vertex_a, vertex_b, point)) {
            intersection_count++;
        }
    }
    
    return intersection_count % 2 == 1;
}


int PolAlg::findSector(
    Point2D point,
    Point2D base,
    std::vector<Point2D>::const_iterator start,
    std::vector<Point2D>::const_iterator end) 
{  
                                                            
    auto it = std::partition_point(start, end,
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - base, point - base) >= 0;
        }
    );

    auto it2 = std::partition_point(start, end,
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - *start, point - *start) >= 0;
        }
    );

    std::cout << "pb " << base.x_ << " " << base.y_ << " pb2 " << (*start).x_ << " " << (*start).y_ << std::endl;

    return static_cast<int>(std::distance(start, it)) - 1;
}




bool PolAlg::pointInStarPolygon(Point2D point,
                                Point2D base,
                                std::vector<Point2D>::const_iterator start,
                                std::vector<Point2D>::const_iterator end) {

    int left = findSector(point, base, start, end);
    int right = (left == std::distance(start, end) - 1) ? 0 : left + 1;

    if(left == -1){
        right = 0;
        left = std::distance(start, end) - 1;
    }
    std::cout << left << " " << right << std::endl;

    // Используем ориентацию для проверки принадлежности звездному многоугольнику
    if(LinealAlgebra::orientation(*(start + left), *(start + right), point) == LinealAlgebra::Orientations::Right)
        return true;

    return false;
}