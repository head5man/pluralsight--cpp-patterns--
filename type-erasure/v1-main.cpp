#include "circle.h"
#include "square.h"
#include <vector>
#include <memory>
/// @brief Code presented by Klaus Iglberger in CppCon 2022
///
/// [Breaking Dependencies - C++ Type Erasure](https://www.youtube.com/watch?v=qn6OqefuH08)
struct ShapeConcept
{
    virtual ~ShapeConcept() = default;

    virtual void do_serialize( /*...*/ ) const = 0;
    virtual void do_draw( /*...*/ ) const = 0;
};

template< typename ShapeT >
struct ShapeModel : public ShapeConcept
{
    ShapeModel( ShapeT shape )
        : shape_{ std::move(shape) }
    {}

    /// The implementation of the virtual functions
    /// in the ShapeModel class defines the affordances
    // required by the type shapeT
    void do_serialize( /*...*/ ) const override
    {
        serialize( shape_ /*, ...*/ );
    }

    void do_draw( /*...*/ ) const override
    {
        draw( shape_ /*, ...*/ );
    }

    ShapeT shape_;
};

/// These functions resolve the requirements posed
/// by the External Polymorphism design pattern.
/// @param  
void serialize( Circle const& /*, ...*/ );
void draw( Circle const& /*, ...*/ );

void serialize( Square const& /*, ...*/ );
void draw( Square const& /*, ...*/ );

void drawAllShapes( std::vector<std::unique_ptr<ShapeConcept>> const& shapes )
{
    for (auto const& shape : shapes)
    {
        shape->do_draw();
    }
}

void serializeAllShapes( std::vector<std::unique_ptr<ShapeConcept>> const& shapes )
{
    for (auto const& shape : shapes)
    {
        shape->do_serialize();
    }
}

int main()
{
    using Shapes = std::vector<std::unique_ptr<ShapeConcept>>;

    // Creating some shapes
    Shapes shapes;
    shapes.emplace_back( std::make_unique<ShapeModel<Circle>>( 2.0 ));
    shapes.emplace_back( std::make_unique<ShapeModel<Square>>( 1.5 ));
    shapes.emplace_back( std::make_unique<ShapeModel<Circle>>( 4.2 ));

    // Drawing all shapes
    drawAllShapes( shapes );
    // Serializing all shapes
    serializeAllShapes( shapes );
}