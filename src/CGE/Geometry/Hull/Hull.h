#ifndef CREATE_HULL_H
#define CREATE_HULL_H

#include <functional>
#include <random>

#include "HullAlgorithms.h"

class Hull{
private:
    std::vector<Point2D> hull_;

    using CreateHull = std::function<std::vector<Point2D>(
        std::vector<Point2D>::const_iterator,
        std::vector<Point2D>::const_iterator
    )>;
    
    CreateHull create_hull_;

public:
    
    Hull(int count_dots, CreateHull function){

        if(count_dots < 10)
            throw std::invalid_argument("Error: Задано неверное количество точек.");


        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<> dist(0, count_dots);

        for(int i = 0; i < count_dots; i++)
            hull_.push_back(Point2D(dist(gen), dist(gen)));

            create_hull_ = function;
    };

    std::vector<Point2D> GetHull(){
        return create_hull_(hull_.begin(), hull_.end());
    }

    void Regenerate(){
        Hull temp_hull(hull_.size(), create_hull_); 

        *this = std::move(temp_hull); 
    }

        // Возвращает исходный набор точек (меш)
    std::vector<Point2D> GetAllPoints() const {
        return hull_; // исходные точки, до применения create_hull_
    }

};


#endif //CREATE_HULL_H
