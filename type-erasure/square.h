#pragma once
#include "utils/source-utils.h"
#include <iostream>


class Square
{
private:
    double side_;
public:
    Square(double side)
        : side_(side)
    {}

    void draw( /*...*/ ) const 
    {
        std::cout << utils::source::filename() << ":" << utils::source::function() << ": side(" << side_ << ")" << std::endl;
    }

    void serialize ( /*...*/) const
    {
        std::cout << utils::source::filename() << ":" << utils::source::function() << ": side(" << side_ << ")" << std::endl;
    }
};
