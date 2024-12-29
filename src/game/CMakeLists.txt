cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(PokerLib Bets.cpp
                     BettingRound.cpp
                     Board.cpp
                     Card.cpp
                     CardParser.cpp
                     Combinations.cpp
                     Deck.cpp
                     Game.cpp
                     Hand.cpp
                     HoleCards.cpp
                     PlayerId.cpp
                     PlayersInHand.cpp
                     Pot.cpp
                     Potential.cpp
                     Strength.cpp
                     TableCards.cpp
                     WinningProbabilities.cpp)

target_include_directories(
  PokerLib
  PUBLIC ../../include/game
)
