#include <gtest/gtest.h>
#include <array>

#include "Card.h"
#include "HandEvaluator.h"
#include "HandRanker.h"


TEST(HandRankerTest, Winner) { 
    std::array<Card, 2> hand1{Card(Value::ACE, Suit::SPADES), Card(Value::KING, Suit::SPADES)};
    std::array<Card, 2> hand2{Card(Value::ACE, Suit::CLUBS), Card(Value::ACE, Suit::DIAMONDS)};

    std::array<Card, 5> board{Card(Value::EIGHT, Suit::SPADES), Card(Value::THREE, Suit::SPADES), Card(Value::FOUR, Suit::SPADES), Card(Value::FIVE, Suit::SPADES), Card(Value::SIX, Suit::SPADES)};

    Winner result = getWinner({hand1, hand2}, board);

    EXPECT_EQ(result.hasWinner, true);
    EXPECT_EQ(result.winnerIdx, 0);
}

TEST(HandRankerTest, StraightFlushEvaluation) {
    std::array<Card, 2> hand1{Card(Value::ACE, Suit::DIAMONDS), Card(Value::KING, Suit::CLUBS)};
    std::array<Card, 5> board{Card(Value::TWO, Suit::SPADES), Card(Value::THREE, Suit::SPADES), Card(Value::FOUR, Suit::SPADES), Card(Value::FIVE, Suit::SPADES), Card(Value::SIX, Suit::SPADES)};

    HandEvaluation result = bestEvaluation(hand1, board);

    EXPECT_EQ(result.rank, HandRank::STRAIGHT_FLUSH);
    std::vector<Value> kicker = {Value::SIX};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandRankerTest, Tie) { 
    std::array<Card, 2> hand1{Card(Value::ACE, Suit::DIAMONDS), Card(Value::KING, Suit::CLUBS)};
    std::array<Card, 2> hand2{Card(Value::ACE, Suit::CLUBS), Card(Value::ACE, Suit::HEARTS)};

    std::array<Card, 5> board{Card(Value::TWO, Suit::SPADES), Card(Value::THREE, Suit::SPADES), Card(Value::FOUR, Suit::SPADES), Card(Value::FIVE, Suit::SPADES), Card(Value::SIX, Suit::SPADES)};

    Winner result = getWinner({hand1, hand2}, board);

    EXPECT_EQ(result.hasWinner, false);
}
