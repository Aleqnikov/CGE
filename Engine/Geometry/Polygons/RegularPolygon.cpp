//
// Created by Иван Алейников on 19.09.2025.
//
#include <random>

#include "RegularPolygon.h"

/**
 * @brief Функция определения принадлежности точки многоугольнику.
 * 
 * Применяется метод трассирующей прямой. Те из нашей точки проводится прямая, затем
 * считается количество пересечений с ребрами многоугольника, если их четное количество, 
 * то точка внутри, если нечетное, то точка находится вне многоугольника
 */
bool RegularPolygon::inPolygon(Point2D point){
    int cnt = 0;
    int n = vertices.size();
    for(int i = 0; i < n; i++)
        if(LinealAlgebra::cross_rib(vertices[i], vertices[(i+1)%n], point))
            cnt++;
    return cnt % 2 == 1;
}

/**
 * @brief Конструктор  многоугольника.
 * 
 * Инвариант - количество вершин - всегда больше 2.
 * 
 * Идея - мы выбираем необходимое число точек на окружности затем случайно генерируем радиусы.
 */
 RegularPolygon::RegularPolygon(int count_vertices) {

    if(count_vertices < 3)
        throw std::invalid_argument("Count vertices was been more then 2!");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

    std::vector<double> angles(count_vertices);

    for (int i = 0; i < count_vertices; ++i) 
        angles[i] = angleDist(gen);
    
    std::sort(angles.begin(), angles.end());                                    // для ориентации многоугольника против часовой стрелки

    std::uniform_real_distribution<> radDist(0, 2 * count_vertices);

    for (double a : angles) {
        double r = radDist(gen);              
        vertices.push_back({r * std::cos(a), r * std::sin(a)});
    }

}

 void RegularPolygon::Regenerate(){

     int count_vertices = vertices.size();

     vertices.clear();

     std::random_device rd;
     std::mt19937 gen(rd());
     std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

     std::vector<double> angles(count_vertices);

     for (int i = 0; i < count_vertices; ++i)
         angles[i] = angleDist(gen);

     std::sort(angles.begin(), angles.end());                                    // для ориентации многоугольника против часовой стрелки

     std::uniform_real_distribution<> radDist(0, 2 * count_vertices);

     for (double a : angles) {
         double r = radDist(gen);
         vertices.push_back({r * std::cos(a), r * std::sin(a)});
     }
 }
