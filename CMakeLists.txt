cmake_minimum_required(VERSION 4.1.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(m3)

add_executable(${PROJECT_NAME} src/main.cpp src/str.cpp src/sys.cpp)