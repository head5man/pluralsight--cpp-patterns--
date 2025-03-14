#include "circle.h"
#include "square.h"

void serialize( Circle const& shape /*, ...*/ ){ shape.serialize(); }
void draw( Circle const& shape /*, ...*/ ) { shape.draw(); }

void serialize( Square const& shape /*, ...*/ ){ shape.serialize(); }
void draw( Square const& shape /*, ...*/ ) { shape.draw(); }