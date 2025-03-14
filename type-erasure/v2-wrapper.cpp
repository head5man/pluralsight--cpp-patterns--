/// @brief Code presented by Klaus Iglberger in CppCon 2022
///
/// [Breaking Dependencies - C++ Type Erasure](https://www.youtube.com/watch?v=qn6OqefuH08)
#include <memory>

#include "circle.h"
#include "square.h"

#include <vector>

// These functions resolve the requirements posed
// by the External Polymorphism design pattern.
void serialize( Circle const& /*, ...*/ );
void serialize( Square const& /*, ...*/ );
#if 1
#include "v3-shape-const-ref.h"
// ShapeModel::DoDraw calls this
void draw( ShapeConstRef shape )
{
    std::cout << utils::source::function() << std::endl;
}
#else
void draw( Circle const& /*, ...*/ );
void draw( Square const& /*, ...*/ );
#endif

class Shape
{
private:
    struct ShapeConcept
    {
        virtual ~ShapeConcept() = default;

        virtual void do_serialize( /*...*/ ) const = 0;
        virtual void do_draw( /*...*/ ) const = 0;
        virtual std::unique_ptr<ShapeConcept> clone() const = 0;
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
            std::cout << utils::source::function() << std::endl;
            draw( shape_ /*, ...*/ );
        }

        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ShapeModel>(*this);
        }

        ShapeT shape_;
    };

    template< typename ShapeT, typename DrawStrategy >
    struct ExtendedModel : public ShapeConcept
    {
        explicit ExtendedModel( ShapeT shape, DrawStrategy drawer)
            :
            shape_( std::move(shape) ),
            drawer_( std::move(drawer) )
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
            drawer_( shape_ /*, ...*/ );
        }

        std::unique_ptr<ShapeConcept> clone() const override
        {
            return std::make_unique<ExtendedModel>(*this);
        }

        ShapeT shape_;
        DrawStrategy drawer_;
    };

    /// Despite being defined inside the class definition,
    /// these friend functions are free functions and
    /// injected into the surrounding namespace
    friend void serialize( Shape const& shape /*, ...*/)
    {
        shape.pimpl->do_serialize();
    }

    friend void draw( Shape const& shape /*, ...*/)
    {
        shape.pimpl->do_draw();
    }

    std::unique_ptr<ShapeConcept> pimpl;

public:
    /// @brief A templated constructor, creating a bridge
    template<typename ShapeT> Shape(ShapeT shape)
        : pimpl( std::make_unique<ShapeModel<ShapeT>>( std::move( shape ) ) )
        {}

    /// @brief A templated constructor, creating a bridge
    template<typename ShapeT, typename DrawStrategy> Shape(ShapeT shape, DrawStrategy drawer)
        : pimpl( std::make_unique<ExtendedModel<ShapeT, DrawStrategy>>( std::move( shape ), std::move(drawer) ) )
    {}

    // Copy operations
    Shape( Shape const& other )
        : pimpl( other.pimpl->clone() )
    {}

    Shape& operator=( Shape const& other )
    {
        // copy-and-swap idiom
        other.pimpl->clone().swap( pimpl );
        return *this;
    }

    // Move operations
#if 1 // option1
    // moved-from shapes are semantically equivalent to a nullptr

    Shape( Shape && other ) = default;
    Shape& operator=( Shape&& other ) = default;
#elif option2
    // Move remains undefined, copy serves as a fallback

    // Shape( Shape && other );
    // Shape& operator=( Shape&& other );
#elif option3
    // The move constructor is undefined,
    // the move assignment operator is
    // implemented in terms of swap.

    // Shape( Shape && other );
    Shape& operator=( Shape&& other ) noexcept
    {
        pimpl.swap( other.pimpl );
        return *this;
    }
#endif
};

void drawAllShapes( std::vector<Shape> const& shapes )
{
    for (auto const& shape : shapes)
    {
        draw(shape);
    }
}

void serializeAllShapes( std::vector<Shape> const& shapes )
{
    for (auto const& shape : shapes)
    {
        serialize(shape);
    }
}

int main()
{
    using Shapes = std::vector<Shape>;

    // Creating some shapes
    Shapes shapes;
    shapes.emplace_back( Circle( 2.0 ));
    shapes.emplace_back( Square( 1.5 ));
    shapes.emplace_back( Circle( 4.2 ));
    shapes.emplace_back( Circle{ 6.6 }, []( Circle const& circle ){
        std::cout << "injected lambda" << std::endl;
        circle.draw();
    }
    );

    // Drawing all shapes
    drawAllShapes( shapes );
    // Serializing all shapes
    serializeAllShapes( shapes );
}