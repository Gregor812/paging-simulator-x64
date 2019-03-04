cmake_minimum_required(VERSION 3.5)

project(Paging
    LANGUAGES ASM C CXX
)

add_executable(
    App
    ${CMAKE_SOURCE_DIR}/main.cpp
)

set_property(TARGET App PROPERTY CXX_STANDARD 14)
