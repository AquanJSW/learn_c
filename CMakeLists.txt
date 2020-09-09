cmake_minimum_required(VERSION 3.5)
project(learn_c C)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_C_STANDARD 99)

add_executable(learn_c main.c)

target_link_libraries(learn_c ${OpenCV_LIBS})