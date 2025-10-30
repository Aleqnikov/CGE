
#include "ConvexPolygon.h"

ConvexPolygon::ConvexPolygon(int count_vertices, InPolygonChecker checker_func) {

    if(count_vertices < 3)
        throw std::invalid_argument("Count vertices was been more then 2!");

    std::set<int> vertices_uniq;

    std::random_device rd;
    std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> dist(0, 2*count_vertices - 1);

    while(vertices_uniq.size() != count_vertices)
        vertices_uniq.insert(dist(gen));
    

    
    for(auto angle : vertices_uniq)
        vertices.push_back(Point2D(
            count_vertices*std::cos(2* M_PI * angle / (2*count_vertices )), 
            count_vertices*std::sin(2* M_PI * angle / (2*count_vertices )))
    );

    

    checker_func_ = checker_func;
}


void ConvexPolygon::Regenerate() {
    ConvexPolygon temp_polygon(vertices.size(), checker_func_); 

    *this = std::move(temp_polygon); 
}