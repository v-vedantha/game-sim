cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.87) 

add_executable(
    ServerTest GameLifecycle.cpp)

target_link_libraries(
  ServerTest
  PRIVATE GTest::gtest_main
  PRIVATE Server
)

target_include_directories(
  ServerTest
  PRIVATE ../../include/server
  PRIVATE  ${Boost_INCLUDE_DIRS}
)

include(GoogleTest)
gtest_discover_tests(ServerTest)

