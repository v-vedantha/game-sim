
cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(TestLib  TestUtils.cpp )

add_executable(
  CardParserTest
  CardParserTest.cpp
  HandTest.cpp
  GameOddsTest.cpp
  HandPotentialTest.cpp
  FullGameTest.cpp
)

target_link_libraries(
  CardParserTest
  PUBLIC GTest::gtest_main
  PUBLIC PokerLib
  PUBLIC TestLib
)

target_include_directories(
  CardParserTest
  PUBLIC ../../include/game
)

include(GoogleTest)
gtest_discover_tests(CardParserTest)
