cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(
    CliTest CreateConnection.cpp)


target_link_libraries(
  CliTest
  PUBLIC GTest::gtest_main
  PUBLIC Cli
)

target_include_directories(
  CliTest
  PUBLIC ../../include/cli
)

include(GoogleTest)
gtest_discover_tests(CliTest)

