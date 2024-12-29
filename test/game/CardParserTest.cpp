#include "CardParser.h"
#include "Card.h"
#include <gtest/gtest.h>

TEST(CardParsingTest, AceOfSpades) {
    EXPECT_EQ(parseCard("AS"), Card(Value::ACE, Suit::SPADES));
};

TEST(CardParsingTest, TenOfHearts) {
    EXPECT_EQ(parseCard("10h"), Card(Value::TEN, Suit::HEARTS));
};

TEST(CardParsingTest, ElevenCausesException) {
    EXPECT_THROW(parseCard("11h"), ParseFailed);
};

TEST(CardParsingTest, MultipleCards) {
    std::vector<Card> expectedOutput = {Card(Value::TEN, Suit::HEARTS),
                                        Card(Value::NINE, Suit::SPADES)};
    EXPECT_EQ(parseCards("10h9s"), expectedOutput);
};
