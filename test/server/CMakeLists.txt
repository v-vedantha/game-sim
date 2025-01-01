cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.87) 
include_directories( ${Boost_INCLUDE_DIR} )

add_executable(
    ServerTest GameLifecycle.cpp)


target_link_libraries(
  ServerTest
  PUBLIC GTest::gtest_main
  PUBLIC Server
)

target_include_directories(
  ServerTest
  PUBLIC ../../include/server
)

include(GoogleTest)
gtest_discover_tests(ServerTest)

