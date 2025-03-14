# Add source to this project's executable.
add_library (utils "source-utils.cpp")
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET utils PROPERTY CXX_STANDARD 20)
endif()