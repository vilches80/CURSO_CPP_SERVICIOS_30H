# CMakeList.txt: proyecto de CMake para practica2_multistage, incluya el origen y defina
# la lógica específica del proyecto aquí.
#
# TODO: Agregue pruebas y destinos de instalación si es necesario.

cmake_minimum_required(VERSION 3.8)
project(practica3_vcpkg)

add_executable(practica3_vcpkg practica3.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(practica3_vcpkg PRIVATE fmt::fmt)

set_property(TARGET practica3_vcpkg PROPERTY CXX_STANDARD 20)
