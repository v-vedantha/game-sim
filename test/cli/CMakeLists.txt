cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    CliTest CreateConnection.cpp)

target_include_directories(
  CliTest
  PRIVATE ../../include/cli
  PRIVATE ../../include/server
)

target_link_libraries(
  CliTest
  PRIVATE GTest::gtest_main
  PRIVATE Cli
  PRIVATE Server
)

include(GoogleTest)
gtest_discover_tests(CliTest)

