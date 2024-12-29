cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Cli Main.cpp
                Command.cpp
                Context.cpp
                Connection.cpp
                Shell.cpp)

target_include_directories(
    Cli
    PUBLIC ../../include/cli
)
