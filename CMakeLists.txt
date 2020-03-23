cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(sample_motion_model_velocity)

find_package (OpenCV REQUIRED)

add_executable(prog1 prog1.cpp)
add_executable(prog2 prog2.cpp)
add_executable(prog3 prog3.cpp)
add_executable(prog4 prog4.cpp)

target_link_libraries(prog1 ${OpenCV_LIBRARIES})
target_link_libraries(prog2 ${OpenCV_LIBRARIES})
target_link_libraries(prog3 ${OpenCV_LIBRARIES})
target_link_libraries(prog4 ${OpenCV_LIBRARIES})
