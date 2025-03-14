# Add source to this project's executable.
add_executable (v1-free-functions "v1-main.cpp" "v1-free-functions.cpp")
target_link_libraries(v1-free-functions utils)

add_executable(v2-wrapper "v2-wrapper.cpp" "v1-free-functions.cpp")
target_link_libraries(v2-wrapper utils)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET v1-free-functions PROPERTY CXX_STANDARD 20)
  set_property(TARGET v2-wrapper PROPERTY CXX_STANDARD 20)
endif()