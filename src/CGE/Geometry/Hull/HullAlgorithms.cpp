#include "HullAlgorithms.h"


namespace HullAlg = HullAlgorithms;
namespace LinAl = LinealAlgebra;

std::vector<Point2D> HullAlg::JarvisMarch (std::vector<Point2D>::const_iterator begin,
                                            std::vector<Point2D>::const_iterator end) 
{
    int size = std::distance(begin, end);
    if (size < 3) return std::vector<Point2D>(begin, end);

    std::vector<Point2D> hull;

    int left_idx = 0;
    for (int i = 1; i < size; i++) {
        if (begin[i].x_ < begin[left_idx].x_ || 
           (begin[i].x_ == begin[left_idx].x_ && begin[i].y_ < begin[left_idx].y_)) {
            left_idx = i;
        }
    }

    int p = left_idx;
    int q;

    hull.push_back(begin[p]); 

    while (true) {
        q = (p + 1) % size;

        for (int i = 0; i < size; ++i) {
            if (i == p) continue;
            
            if (LinAl::orientation(begin[p], begin[q], begin[i]) == LinAl::Orientations::Right) {
                q = i;
            }
        }

        p = q;
        if (p == left_idx) break; 
        hull.push_back(begin[p]);
    }

    return hull;
}

// Исправлено: добавлено пространство имен
std::vector<Point2D> GrahamScan(std::vector<Point2D>::const_iterator begin,
                                         std::vector<Point2D>::const_iterator end)
{
    std::vector<Point2D> points(begin, end);
    if (points.size() < 3)
        return points;

    // Находим точку с минимальной y-координатой (и минимальной x при равенстве y)
    auto pivot_it = std::min_element(points.begin(), points.end(),
        [](const Point2D& a, const Point2D& b) {
            return (a.y_ < b.y_) || (a.y_ == b.y_ && a.x_ < b.x_);
        });

    Point2D pivot = *pivot_it;
    std::iter_swap(points.begin(), pivot_it);

    // Сортируем по полярному углу относительно pivot
    std::sort(points.begin() + 1, points.end(),
        [&pivot](const Point2D& a, const Point2D& b) {
            auto orient = LinAl::orientation(pivot, a, b);
            if (orient == LinAl::Orientations::Colinear)
                return LinAl::distance(pivot, a) < LinAl::distance(pivot, b);
            return orient == LinAl::Orientations::Left;
        });

    // Удаляем коллинеарные точки (оставляем самую дальнюю)
    size_t j = 1;
    for (size_t i = 2; i < points.size(); i++) {
        while (j > 0 && LinAl::orientation(points[j-1], points[j], points[i]) == LinAl::Orientations::Colinear) {
            j--;
        }
        points[++j] = points[i];
    }
    points.resize(j + 1);

    // Строим выпуклую оболочку
    std::vector<Point2D> hull;
    hull.reserve(points.size());
    hull.push_back(points[0]);
    
    if (points.size() > 1) {
        hull.push_back(points[1]);
    }

    for (size_t i = 2; i < points.size(); ++i) {
        while (hull.size() >= 2 &&
               LinAl::orientation(hull[hull.size() - 2],
                                 hull.back(),
                                 points[i]) != LinAl::Orientations::Left) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    return hull;
}

std::vector<Point2D> HullAlg::Andrews(std::vector<Point2D>::const_iterator start,
                                      std::vector<Point2D>::const_iterator end)
{
    std::vector<Point2D> points(start, end);
    if (points.size() < 3)
        return points;

    // Сортируем точки по x (и по y при равенстве x)
    std::sort(points.begin(), points.end(),
        [](const Point2D& a, const Point2D& b) {
            return (a.x_ < b.x_) || (a.x_ == b.x_ && a.y_ < b.y_);
        });

    // Удаляем дубликаты
    auto last = std::unique(points.begin(), points.end(),
        [](const Point2D& a, const Point2D& b) {
            return a.x_ == b.x_ && a.y_ == b.y_;
        });
    points.erase(last, points.end());

    if (points.size() < 3)
        return points;

    // Разделяем на нижнюю и верхнюю оболочки
    std::vector<Point2D> lower, upper;
    
    // Нижняя оболочка
    for (const auto& p : points) {
        while (lower.size() >= 2 && 
               LinAl::orientation(lower[lower.size()-2], lower.back(), p) != LinAl::Orientations::Left) {
            lower.pop_back();
        }
        lower.push_back(p);
    }
    
    // Верхняя оболочка
    for (auto it = points.rbegin(); it != points.rend(); ++it) {
        while (upper.size() >= 2 && 
               LinAl::orientation(upper[upper.size()-2], upper.back(), *it) != LinAl::Orientations::Left) {
            upper.pop_back();
        }
        upper.push_back(*it);
    }
    
    // Объединяем (убираем дублирующиеся крайние точки)
    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();
    
    lower.insert(lower.end(), upper.begin(), upper.end());
    
    return lower;
}