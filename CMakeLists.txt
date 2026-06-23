cmake_minimum_required(VERSION 3.20)

project(GeometryLab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(geometry
    src/Vec2.cpp
    src/Vec3.cpp
    src/Segment2.cpp
    src/Segment3.cpp
    src/Distance.cpp
)


target_include_directories(geometry PUBLIC include)

add_executable(demo
    examples/demo.cpp
)

target_link_libraries(demo PRIVATE geometry)

add_executable(tests
    tests/tests.cpp
)

target_link_libraries(tests PRIVATE geometry)