//
// Created by Иван Алейников on 19.09.2025.
//
#include <set>
#include <random>
#include <cmath>

#include "ConvexPolygon.h"

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
bool ConvexPolygon::inPolygon(Point2D point){
    return LinealAlgebra::PointInConvexPolygon(vertices.begin(), vertices.end(), point);
}


/**
 * @brief Конструктор выпуклого многоугольника.
 * 
 * Инвариант - количество вершин - всегда больше 2.
 * 
 * Идея - мы выбираем необходимое число точек на окружности.
 * 
 * Заполняем множество n различных значений, затем, отсортировав, при помощи системы полярных координат
 * переводим это значение в стандарный вид.
 */
ConvexPolygon::ConvexPolygon(int count_vertices) {

    if(count_vertices < 3)
        throw std::invalid_argument("Count vertices was been more then 2!");

    std::set<int> vertices_uniq;

    std::random_device rd;
    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> dist(0, count_vertices);

    while(vertices_uniq.size() != count_vertices)
        vertices_uniq.insert(dist(gen));
    
    for(auto angle : vertices_uniq)
        vertices.push_back(Point2D(
            count_vertices*std::cos(2* M_PI * angle / count_vertices), 
            count_vertices*std::sin(2* M_PI * angle / count_vertices))
    );


}

void ConvexPolygon::Regenerate(){
    std::set<int> vertices_uniq;

    std::random_device rd;
    std::mt19937 gen(rd());

    int count_vertices = vertices.size();

    vertices.clear();

    std::uniform_int_distribution<> dist(0, count_vertices);

    while(vertices_uniq.size() != count_vertices)
        vertices_uniq.insert(dist(gen));

    for(auto angle : vertices_uniq)
        vertices.push_back(Point2D(
            count_vertices*std::cos(2* M_PI * angle / count_vertices),
            count_vertices*std::sin(2* M_PI * angle / count_vertices))
    );
}
