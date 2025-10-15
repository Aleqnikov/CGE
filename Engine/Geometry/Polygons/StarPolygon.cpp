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

bool StarPolygon::inPolygon(Point2D point){
    return LinealAlgebra::PointInConvexPolygon(vertices.begin(), vertices.end(), point);
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
