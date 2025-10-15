#include "CreateMesh.h"

#include <random>


Mesh::Mesh(int count){

    if(count < 10)
        throw std::invalid_argument("Error: Задано неверное количество точек.");


    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dist(0, count);

    for(int i = 0; i < count; i++)
        mesh.push_back(Point2D(dist(gen), dist(gen)));
}

Mesh::Mesh() : Mesh(10) {};


std::vector<Point2D> Mesh::JarvisMarch() {

    std::vector<Point2D> mesh1;

    int left = 0;
    for (int i = 1; i < mesh.size(); i++)
        if (mesh[i].x < mesh[left].x || 
           (mesh[i].x == mesh[left].x && mesh[i].y < mesh[left].y))
            left = i;

    int p = left, q;

    mesh1.push_back(mesh[p]); // добавляем стартовую точку

    while (true) {
        q = (p + 1) % mesh.size();

        for (int i = 0; i < mesh.size(); ++i) {
            if (i == p) continue;
            if (LinealAlgebra::orientation(mesh[p], mesh[q], mesh[i]) == LinealAlgebra::Orientations::Right)
                q = i;
        }

        p = q;
        if (p == left) break;   // достигли стартовой точки — завершение
        mesh1.push_back(mesh[p]);
    }

    return mesh1;
}