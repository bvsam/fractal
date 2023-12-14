cmake_minimum_required(VERSION 3.8)
project(fractal LANGUAGES CXX)

set(SFML_LIBS sfml-graphics sfml-system sfml-window)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})
