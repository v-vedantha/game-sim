cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.87) 
include_directories( ${Boost_INCLUDE_DIR} )



add_library(Server  Server.cpp)



target_include_directories(
    Server
    PUBLIC ../../include/server
)

