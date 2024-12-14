#include <gtest/gtest.h>
#include <iostream>
#include "Card.h"
#include "Game.h"
#include "PlayerId.h"
#include "TestUtils.h"


bool isIn(PlayerId player, std::vector<PlayerId> players) {
    for (PlayerId p : players) {
        if (p == player) {
            return true;
        }
    }
    return false;
}

TEST(GameTest, Tie) {
    PlayerId p1 = PlayerId("P1");
    PlayerId p2 = PlayerId("P2");
    Game game = Game({p1, p2});
    game.dealToPlayer(p1, {Card(Value::TWO, Suit::HEARTS), Card(Value::TWO, Suit::CLUBS)});
    game.dealToPlayer(p2, {Card(Value::ACE, Suit::HEARTS), Card(Value::ACE, Suit::CLUBS)});
    game.dealToBoard({Card(Value::ACE, Suit::SPADES),
                      Card(Value::TWO, Suit::SPADES),
                      Card(Value::FIVE, Suit::SPADES), 
                      Card(Value::FOUR, Suit::SPADES), 
                      Card(Value::THREE, Suit::SPADES)});


    std::vector<PlayerId> winners = game.getWinners();

    EXPECT_TRUE(isIn(p1, winners));
    EXPECT_TRUE(isIn(p2, winners));
}

TEST(EquitiesTest, PairVsPair) {
    PlayerId p1 = PlayerId("P1");
    PlayerId p2 = PlayerId("P2");
    Game game = Game({p1, p2});
    game.dealToPlayer(p1, {Card(Value::TWO, Suit::HEARTS), Card(Value::TWO, Suit::CLUBS)});
    game.dealToPlayer(p2, {Card(Value::ACE, Suit::HEARTS), Card(Value::ACE, Suit::CLUBS)});

    Equities equities = game.equities(42);

    EXPECT_TRUE(isNear(equities.getEquity(p1), 0.13));
    EXPECT_TRUE(isNear(equities.getEquity(p2), 0.87));
}


TEST(EquitiesTest, PairVsOverCards) {
    PlayerId p1 = PlayerId("P1");
    PlayerId p2 = PlayerId("P2");
    Game game = Game({p1, p2});
    game.dealToPlayer(p1, {Card(Value::TWO, Suit::HEARTS), Card(Value::TWO, Suit::CLUBS)});
    game.dealToPlayer(p2, {Card(Value::ACE, Suit::HEARTS), Card(Value::JACK, Suit::CLUBS)});

    Equities equities = game.equities(42);

    EXPECT_TRUE(isNear(equities.getEquity(p1), 0.58));
    EXPECT_TRUE(isNear(equities.getEquity(p2), 0.43));
}
