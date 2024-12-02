#include <gtest/gtest.h>
#include <array>
#include "HandEvaluator.h"

TEST(HandEvaluatorTest, StraightFlush) {
    std::array<Card, 5> hand = {
        Card(Value::ACE, Suit::CLUBS),
        Card(Value::TWO, Suit::CLUBS),
        Card(Value::THREE, Suit::CLUBS),
        Card(Value::FOUR, Suit::CLUBS),
        Card(Value::FIVE, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::STRAIGHT_FLUSH);
    std::vector<Value> kicker = {Value::FIVE};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, Quads) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::SIX, Suit::CLUBS),
        Card(Value::SIX, Suit::DIAMONDS),
        Card(Value::SIX, Suit::HEARTS),
        Card(Value::SEVEN, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::FOUR_OF_A_KIND);
    std::vector<Value> kicker = {Value::SIX, Value::SEVEN};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, Straight) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::TWO, Suit::CLUBS),
        Card(Value::THREE, Suit::DIAMONDS),
        Card(Value::FOUR, Suit::HEARTS),
        Card(Value::FIVE, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::STRAIGHT);
    std::vector<Value> kicker = {Value::SIX};
    EXPECT_EQ(result.kickers, kicker);
}


TEST(HandEvaluatorTest, Flush) {
    std::array<Card, 5> hand = {
        Card(Value::JACK, Suit::DIAMONDS),
        Card(Value::TWO, Suit::DIAMONDS),
        Card(Value::THREE, Suit::DIAMONDS),
        Card(Value::FOUR, Suit::DIAMONDS),
        Card(Value::FIVE, Suit::DIAMONDS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::FLUSH);
    std::vector<Value> kicker = {Value::JACK};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, FULL_HOUSE) {
    std::array<Card, 5> hand = {
        Card(Value::ACE, Suit::SPADES),
        Card(Value::SEVEN, Suit::CLUBS),
        Card(Value::SEVEN, Suit::DIAMONDS),
        Card(Value::ACE, Suit::HEARTS),
        Card(Value::SEVEN, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::FULL_HOUSE);
    std::vector<Value> kicker = {Value::SEVEN, Value::ACE};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, Trips) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::SEVEN, Suit::CLUBS),
        Card(Value::SEVEN, Suit::DIAMONDS),
        Card(Value::ACE, Suit::HEARTS),
        Card(Value::SEVEN, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::THREE_OF_A_KIND);
    std::vector<Value> kicker = {Value::SEVEN, Value::ACE, Value::SIX};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, TwoPair) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::SEVEN, Suit::CLUBS),
        Card(Value::SEVEN, Suit::DIAMONDS),
        Card(Value::ACE, Suit::HEARTS),
        Card(Value::SIX, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::TWO_PAIR);
    std::vector<Value> kicker = {Value::SEVEN, Value::SIX, Value::ACE};
    EXPECT_EQ(result.kickers, kicker);
}

TEST(HandEvaluatorTest, Pair) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::SEVEN, Suit::CLUBS),
        Card(Value::SEVEN, Suit::DIAMONDS),
        Card(Value::ACE, Suit::HEARTS),
        Card(Value::EIGHT, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::PAIR);
    std::vector<Value> kicker = {Value::SEVEN, Value::ACE, Value::EIGHT, Value::SIX};
    EXPECT_EQ(result.kickers, kicker);
}


TEST(HandEvaluatorTest, HighCard) {
    std::array<Card, 5> hand = {
        Card(Value::SIX, Suit::SPADES),
        Card(Value::SEVEN, Suit::CLUBS),
        Card(Value::JACK, Suit::DIAMONDS),
        Card(Value::ACE, Suit::HEARTS),
        Card(Value::EIGHT, Suit::CLUBS)
    };

    HandEvaluation result = evaluateHand(hand);

    EXPECT_EQ(result.rank, HandRank::HIGH_CARD);
    std::vector<Value> kicker = {Value::ACE, Value::JACK, Value::EIGHT, Value::SEVEN, Value::SIX};
    EXPECT_EQ(result.kickers, kicker);
}
