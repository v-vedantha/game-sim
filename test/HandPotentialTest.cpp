#include <gtest/gtest.h>
#include <iostream>
#include "Card.h"
#include "Strength.h"
#include "Game.h"
#include "PlayerId.h"
#include "TestUtils.h"

TEST(HandPotentialTest, Set) {
    HoleCards holeCards = HoleCards({Card(Value::TEN, Suit::HEARTS), Card(Value::TEN, Suit::DIAMONDS)});

    Board board = Board();

    Street street = Street::FLOP;
    Potential potential = holeCards.evaluatePotential(board, street, 42);

    Rank targetRank = Rank::THREE_OF_A_KIND;
    std::cout << potential.oddsOfHitting(targetRank) << std::endl;
    EXPECT_TRUE(isNear(potential.oddsOfHitting(targetRank), 0.1));
}
