cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.87 REQUIRED) 



add_library(Uri Uri.cpp)


target_include_directories(
    Uri
    PUBLIC ../../include/uri
    PUBLIC ${Boost_INCLUDE_DIRS}
)

