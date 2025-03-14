#pragma once
#include <iostream>

class ShapeConstRef
{
public:
    template< typename ShapeT >
    ShapeConstRef( ShapeT const& shape )
        : shape_( std::addressof(shape) )
        , draw_{ []( void const* shape ){
            std::cout << "ShapeConstRef::draw_" << std::endl;
            draw( *static_cast<ShapeT const*>(shape) );
        } }
    {
    }

private:

    friend void draw( ShapeConstRef const& shape )
    {
        std::cout << "ShapeConstRef::draw" << std::endl;
        shape.draw_( shape.shape_ );
    }

    using DrawOp = void(void const*);

    void const* shape_{ nullptr };
    DrawOp* draw_{ nullptr };
};