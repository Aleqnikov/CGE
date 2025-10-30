#include "StarPolygon.h"

StarPolygon::StarPolygon(int count_vertices, InPolygonChecker checker_func) {
    if (count_vertices < 2)
        throw std::invalid_argument("Star must have at least 2 spikes");

    // Внешний и внутренний радиусы
    double R_outer = count_vertices;       // можно настраивать
    double R_inner = count_vertices / 2.0;

    vertices.reserve(2 * count_vertices);

    double angle_step = M_PI / count_vertices; // половина угла для чередования

    for (int i = 0; i < 2 * count_vertices; ++i) {
        double radius = (i % 2 == 0) ? R_outer : R_inner;
        double angle = i * angle_step;
        vertices.push_back(Point2D(radius * std::cos(angle), radius * std::sin(angle)));
    }

    checker_func_ = checker_func;
}


void StarPolygon::Regenerate() {
    StarPolygon temp_polygon(vertices.size() / 2, checker_func_); 

    *this = std::move(temp_polygon); 
}