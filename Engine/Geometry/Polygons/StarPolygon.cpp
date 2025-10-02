//
// Created by Иван Алейников on 19.09.2025.
//

#include <set>
#include <random>
#include <cmath>


#include "StarPolygon.h"



/**
 * @brief Конструктор звездного многоугольника.
 * 
 * Инвариант - количество вершин - всегда больше 2.
 * 
 * Идея - мы выбираем необходимое число точек на окружности затем случайно генерируем радиусы.
 */
 StarPolygon::StarPolygon(int count_vertices) {

    if(count_vertices < 3)
        throw std::invalid_argument("Count vertices was been more then 2!");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

    std::set<double> angles;

    while (angles.size() != count_vertices)
        angles.insert(angleDist(gen));

    std::uniform_real_distribution<> radDist(0, 2 * count_vertices);

    for (double a : angles) {
        double r = radDist(gen);              
        vertices.push_back({r * std::cos(a), r * std::sin(a)});
    }


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
int StarPolygon::find_sector(Point2D point){
    Point2D base = Point2D(0,0);                                            // По построению всегда центр звезности.
    std::cout << "find_sector" << std::endl;
    auto it = std::partition_point(vertices.begin(), vertices.end(),
        [&](const Point2D p) {
            return LinealAlgebra::pscalar(p - base, point - base) >= 0;
        }
    );

    return static_cast<int>(std::distance(vertices.begin(), it)) - 1;
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
bool StarPolygon::inPolygon(Point2D point){
    int left = find_sector(point);

    int right = (left == vertices.size() - 1)? 0 : left + 1;

    if(left == -1){
        right = 0;
        left = vertices.size() - 1;
    }

    if(LinealAlgebra::orientation(vertices[left], vertices[right], point) == LinealAlgebra::Orientations::Right)
        return true;




    return false;
}


void StarPolygon::Regenerate(){
    int count_vertices = vertices.size();

    vertices.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

    std::set<double> angles;

    while (angles.size() != count_vertices)
        angles.insert(angleDist(gen));

    std::uniform_real_distribution<> radDist(0, 2 * count_vertices);

    for (double a : angles) {
        double r = radDist(gen);
        vertices.push_back({r * std::cos(a), r * std::sin(a)});
    }

}
