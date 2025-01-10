cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.87) 

add_executable(
    UriTest UriTest.cpp)

target_link_libraries(
  UriTest
  PRIVATE Uri
  PRIVATE GTest::gtest_main
)

target_include_directories(
  UriTest
  PRIVATE ../../include/uri
  PRIVATE  ${Boost_INCLUDE_DIRS}
)

include(GoogleTest)
gtest_discover_tests(UriTest)

