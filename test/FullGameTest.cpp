#include <gtest/gtest.h>
#include <iostream>
#include "Card.h"
#include "PlayerId.h"
#include "Player.h"
#include "Game.h"

TEST(FullTableCardsTest, Showdown) {
    std::shared_ptr<Player> p1 = std::make_shared<Player>(PlayerId("P1"), 20);
    std::shared_ptr<Player> p2 = std::make_shared<Player>(PlayerId("P2"), 20);

    GameBuilder builder;
    builder.addPlayer(p1);
    builder.addPlayer(p2);

    std::shared_ptr<Game> game = builder.build();


    // Assume p1 is the first to act for now since we don't have dealer logic
    // p1 is the small blind, p2 is the big blind.
    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    p1->check();

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P2"));

    p2->raise(10);

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    p1->call();

    game->dealToNextStreet();

    p1->check();
    p2->check();

    game->dealToNextStreet();

    p1->check();
    p2->check();

    game->dealToNextStreet();
    p1->allIn();
    p2->call();

    game->finish();

    EXPECT_EQ(p1->stack(), 0);
    EXPECT_EQ(p2->stack(), 40);
}
