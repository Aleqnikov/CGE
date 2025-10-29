#include "PolygonAlgorithms.h"

namespace LinAl = LinealAlgebra;

namespace PolAlg = PolygonAlgorithms;

using namespace LinAl;




bool PolAlg::pointInStarPolygon(Point2D point,
                                std::vector<Point2D>::const_iterator start,
                                std::vector<Point2D>::const_iterator end) {

   int n = std::distance(start, end);
    if (n < 3) return false;
    
    // Бинарный поиск сектора для выпуклого многоугольника
    int low = 0, high = n - 1;
    
    while (high - low > 1) {
        int mid = (low + high) / 2;
        Point2D ps = *(start + low);   // начальная точка
        Point2D pm = *(start + mid);   // средняя точка
        
        Orientations orient = LinealAlgebra::orientation(ps, pm, point);
        
        if (orient == Orientations::Left) {
            // if orientation(q, ps, pm) == left:
            Point2D p0 = *(start + 0);
            if (LinealAlgebra::orientation(p0, ps, point) != Orientations::Right && 
                LinealAlgebra::orientation(p0, pm, point) == Orientations::Right) {
                // take 1st half
                high = mid;
            } else {
                // take 2nd half
                low = mid;
            }
        } else {
            // else:
            Point2D p0 = *(start + 0);
            if (LinealAlgebra::orientation(p0, ps, point) == Orientations::Right && 
                LinealAlgebra::orientation(p0, pm, point) != Orientations::Right) {
                // take 2nd half
                low = mid;
            } else {
                // take 1st half
                high = mid;
            }
        }
    }
    
    // Проверяем принадлежность треугольнику
    Point2D a = *(start + low);
    Point2D b = *(start + high);
    Point2D c = *(start + 0);
    
    Orientations o1 = LinealAlgebra::orientation(a, b, point);
    Orientations o2 = LinealAlgebra::orientation(b, c, point);
    Orientations o3 = LinealAlgebra::orientation(c, a, point);
    
    // Точка внутри если все ориентации одинаковы (все left или все right)
    return (o1 == o2 && o2 == o3);
}

bool PolAlg::pointInRegularPolygon(Point2D point,
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



int PolygonAlgorithms::findSector(
    Point2D point,
    std::vector<Point2D>::const_iterator start,
    std::vector<Point2D>::const_iterator end) 
{
    Point2D base = Point2D(0,0);     
                                                           
    auto it = std::partition_point(start, end,
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - base, point - base) >= 0;
        }
    );

    return static_cast<int>(std::distance(start, it)) - 1;
}

bool PolAlg::pointInStarPolygon2(Point2D point,
                                std::vector<Point2D>::const_iterator start,
                                std::vector<Point2D>::const_iterator end) {

    int left = findSector(point, start, end);
    int right = (left == std::distance(start, end) - 1) ? 0 : left + 1;

    std::cout << left << " " << right << std::endl;

    // Используем ориентацию для проверки принадлежности звездному многоугольнику
    if(LinealAlgebra::orientation(*(start + left), *(start + right), point) == LinealAlgebra::Orientations::Right)
        return true;

    return false;
}