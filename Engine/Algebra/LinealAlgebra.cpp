//
// Created by Иван Алейников on 19.09.2025.
//

#include "LinealAlgebra.h"

double LinealAlgebra::pscalar(Point2D a, Point2D b) {
    return a.x * b.y - a.y * b.x;
}


/**
 * @breif Поиск ориентации точки с относительно точек а и b
*/
LinealAlgebra::Orientations LinealAlgebra::orientation(Point2D a, Point2D b, Point2D c) {
    double ps_res = pscalar( a - b, c - b);

    if( ps_res > 0 )
        return Orientations::Left;
    else if( ps_res < 0 )
        return Orientations::Right;

    return Orientations::Collinear;
}


/**
 * @brief Данная функция проверяет, пересекает прямая, проведеная из z ребро, задаю
* задающееся точками b, t
*/
bool LinealAlgebra::cross_rib(Point2D a, Point2D b, Point2D p) {
    if(a.y > b.y) std::swap(a, b);

    if(p.y <= a.y || p.y > b.y) return false;

    Orientations o1 = orientation(a, b, p);

    return o1 == Orientations::Right;
}

/**
 * @brief Функция определения принадлежности точки выпуклому многоульнику.
 * 
 * Сначала она находит сектор, которому принадлежит точка, обрабатывает случаей, что если 
 * точка - последняя. И если ориентация искомой точки относительно сектора, которому 
 * она принадлежит - правая, то точка внутри этого сектора, иначе она лежит вне этого сектора.
 * 
 * ВАЖНО!!! В нашем случае все зависит от обхода вершин. В нашем случае обход - против часовой стрелки.
 * В ином случае ориентация должна быть левой.
 */
 bool LinealAlgebra::PointInConvexPolygon(std::vector<Point2D>::const_iterator start,
                            std::vector<Point2D>::const_iterator end, 
                            Point2D point){
    int left = LinealAlgebra::FindSector(point, start, end);
    int right = (left == std::distance(start, end) - 1) ? 0 : left + 1;

    if(LinealAlgebra::orientation(*(start + left), *(start + right), point) == LinealAlgebra::Orientations::Right)
        return true;

    return false;

}

/**
 * @brief Данная функция получает на вход точку, и находит среди секторов выпукого многоу
 * гольника сектор, коему принадлежит точка.
 * 
 * Поиск сектора происходит при помощи бинарного поиска. Мы знаем что многоугольник выпуклый,
 * таким образом все его вершины отсортированы относительно угла полярной системы координат.
 * Сравнение происходит при помощи псевдо скалярного произведения, если оно больше нуля, 
 * значит мы перескачили сектор и нужно идти назад. Те мы ишем последнюю точку, такую что её 
 * псевдо скалярное произведение меньше нуля, а псевдо скалярное произведение следующей точки 
 * больше нуля.
 * 
 * В итоге возвращяется индекс левой вершины ребра.
 * 
 * partition_point — это функция которая находит первый элемент в отсортированном диапазоне, не удовлетворяющий заданному условию 
 */
int LinealAlgebra::FindSector(Point2D point,
                std::vector<Point2D>::const_iterator start, 
                std::vector<Point2D>::const_iterator end){
    Point2D base = Point2D(0,0);     
                                                           
    auto it = std::partition_point(start, end,
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - base, point - base) >= 0;
        }
    );

    return static_cast<int>(std::distance(start, it)) - 1;
}
