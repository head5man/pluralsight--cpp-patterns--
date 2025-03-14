#pragma once
#include "utils/source-utils.h"

#include <iostream>

class Circle
{
private:
    double radius_;
public:
    Circle(double radius)
        : radius_(radius) {}

    void draw( /*...*/ ) const 
    {
        std::cout << utils::source::filename() << ":" << utils::source::function() << ": radius(" << radius_ << ")" << std::endl;
    }
    
    void serialize ( /*...*/) const
    {
        auto source = std::source_location::current();
        std::cout << utils::source::filename(source) << ":" << utils::source::function(source) << ": radius(" << radius_ << ")" << std::endl;
    }
};