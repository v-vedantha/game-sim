#include <gtest/gtest.h>
#include "Card.h"
#include "CardParser.h"

TEST(CardParsingTest, AceOfSpades) {
    EXPECT_EQ(parseCard("AS"), Card(ACE, SPADES));
};

TEST(CardParsingTest, TenOfHearts) {
    EXPECT_EQ(parseCard("10h"), Card(TEN, HEARTS));
};

TEST(CardParsingTest, ElevenCausesException) {
    EXPECT_THROW(parseCard("11h"), ParseFailed);
};

TEST(CardParsingTest, MultipleCards) {
    std::vector<Card> expectedOutput = {Card(TEN, HEARTS), Card(NINE, SPADES)};
    EXPECT_EQ(parseCards("10h9s"), expectedOutput);
};
