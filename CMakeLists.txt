cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(PokerLib src/Bets.cpp
                     src/BettingRound.cpp
                     src/Board.cpp
                     src/Card.cpp
                     src/CardParser.cpp
                     src/Combinations.cpp
                     src/Deck.cpp
                     src/Game.cpp
                     src/Hand.cpp
                     src/HoleCards.cpp
                     src/PlayerId.cpp
                     src/PlayersInHand.cpp
                     src/Pot.cpp
                     src/Potential.cpp
                     src/Strength.cpp
                     src/TableCards.cpp
                     src/WinningProbabilities.cpp)

add_library(TestLib  test/TestUtils.cpp )

add_executable(
  CardParserTest
  test/CardParserTest.cpp
  test/HandTest.cpp
  test/GameOddsTest.cpp
  test/HandPotentialTest.cpp
  test/FullGameTest.cpp
)

target_link_libraries(
  CardParserTest
  PUBLIC GTest::gtest_main
  PUBLIC PokerLib
  PUBLIC TestLib
)

target_include_directories(
  CardParserTest
  PUBLIC include
)

target_include_directories(
  CardParserTest
  PUBLIC test
)

target_include_directories(
  PokerLib
  PUBLIC include
)

include(GoogleTest)
gtest_discover_tests(CardParserTest)
