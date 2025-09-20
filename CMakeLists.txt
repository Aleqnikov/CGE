cmake_minimum_required(VERSION 3.30)
project(CGE)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# Собираем список всех cpp файлов вручную
add_executable(CGE
        main.cpp
        Engine/Algebra/LinealAlgebra.cpp
        Engine/Algebra/Point2D.cpp
        Engine/Geometry/Polygons/ConvexPolygon.cpp
        Engine/Geometry/Polygons/Polygon.cpp
        Engine/Geometry/Polygons/RegularPolygon.cpp
        Engine/Geometry/Polygons/StarPolygon.cpp
)

target_link_libraries(CGE PRIVATE OpenGL::GL GLUT::GLUT)
