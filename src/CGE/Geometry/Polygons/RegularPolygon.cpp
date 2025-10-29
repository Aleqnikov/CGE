#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(int count_vertices, InPolygonChecker checker_func) {

    if(count_vertices < 3)
        throw std::invalid_argument("Count vertices was been more then 2!");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angleDist(0, 2 * M_PI);

    std::vector<double> angles(count_vertices);

    for (int i = 0; i < count_vertices; ++i) 
        angles[i] = angleDist(gen);
    
    std::sort(angles.begin(), angles.end());                                    

    std::uniform_real_distribution<> radDist(0, 2 * count_vertices);

    for (double a : angles) {
        double r = radDist(gen);              
        vertices.push_back({r * std::cos(a), r * std::sin(a)});
    }
    checker_func_ = checker_func;
}

void RegularPolygon::Regenerate() {
    RegularPolygon temp_polygon(vertices.size(), checker_func_); 

    *this = std::move(temp_polygon); 
}