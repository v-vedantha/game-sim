#include "Card.h"
#include "PlayerId.h"
#include "Strength.h"
#include "TableCards.h"
#include "TestUtils.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(HandPotentialTest, Set) {
    std::mt19937 rng(42);
    HoleCards holeCards = HoleCards(
        {Card(Value::TEN, Suit::HEARTS), Card(Value::TEN, Suit::DIAMONDS)});

    Board board = Board();

    Street street = Street::FLOP;
    Potential potential = holeCards.evaluatePotential(board, street, rng);

    EXPECT_TRUE(isNear(potential.oddsOfHitting(Rank::THREE_OF_A_KIND), 0.1));
}
