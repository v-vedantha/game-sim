#include <gtest/gtest.h>
#include "Card.h"
#include "CardParser.h"

TEST(CardParsingTest, CardParsingTest) {
    EXPECT_EQ(parseCard("AS"), Card(SPADES, ACE));
};
