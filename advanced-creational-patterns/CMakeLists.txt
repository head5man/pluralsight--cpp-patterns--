# CMakeList.txt : CMake project for advanced-creational-patterns, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (advanced-creational-patterns "advanced-creational-patterns.cpp" "advanced-creational-patterns.h" "factory-method.cpp" "factory-method.h" "abstract-factory.cpp" "interfaces/coffee.h" "interfaces/coffee-factory.h" "dep-injection/coffee-machine-base.h" "abstract-factory.h"  "dep-injection/icoffee-service.h" "dep-injection/coffee-machine-base.cpp" "dep-injection/proper-coffee-service.h"  "dep-injection/mock-coffee-service.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET advanced-creational-patterns PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
