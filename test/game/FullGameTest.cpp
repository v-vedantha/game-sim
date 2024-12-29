#include "Card.h"
#include "Game.h"
#include "PlayerId.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(FullTableCardsTest, Showdown) {
    // The rest of the game depends on this random seed but I think fixing the
    // seed and letting the game playout is better than ensuring the correct
    // cards get dealt each time.
    std::mt19937 rng(45);
    std::vector<PlayerId> players;
    PlayerId p1 = PlayerId("P1");
    PlayerId p2 = PlayerId("P2");
    players.push_back(p1);
    players.push_back(p2);
    std::unique_ptr<std::unordered_map<PlayerId, int>> chips =
        std::make_unique<std::unordered_map<PlayerId, int>>();
    chips->insert({p1, 20});
    chips->insert({p2, 30});

    std::shared_ptr<Game> game =
        std::make_shared<Game>(players, std::move(chips), rng);

    // Assume p1 is the first to act for now since we don't have dealer logic or
    // blinds
    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    game->check(p1);

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P2"));

    game->raiseTo(p2, 10);

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    game->call(p1);

    game->dealToNextStreet();

    game->check(p1);
    game->check(p2);

    game->dealToNextStreet();

    game->check(p1);
    game->check(p2);

    game->dealToNextStreet();
    game->allIn(p1);
    game->call(p2);

    game->finish();

    EXPECT_EQ(game->stack(p1), 40);
    EXPECT_EQ(game->stack(p2), 10);
}

TEST(FullTableCardsTest, IllegalActionMaintainsState) {
    // The rest of the game depends on this random seed but I think fixing the
    // seed and letting the game playout is better than ensuring the correct
    // cards get dealt each time.
    std::mt19937 rng(45);
    std::vector<PlayerId> players;
    PlayerId p1 = PlayerId("P1");
    PlayerId p2 = PlayerId("P2");
    players.push_back(p1);
    players.push_back(p2);
    std::unique_ptr<std::unordered_map<PlayerId, int>> chips =
        std::make_unique<std::unordered_map<PlayerId, int>>();
    chips->insert({p1, 20});
    chips->insert({p2, 30});

    std::shared_ptr<Game> game =
        std::make_shared<Game>(players, std::move(chips), rng);

    // Assume p1 is the first to act for now since we don't have dealer logic or
    // blinds
    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    game->check(p1);

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P2"));

    game->raiseTo(p2, 10);

    EXPECT_EQ(game->nextIdToAct(), PlayerId("P1"));

    game->call(p1);

    game->dealToNextStreet();

    game->check(p1);
    game->check(p2);

    game->dealToNextStreet();

    game->check(p1);
    game->check(p2);

    game->dealToNextStreet();
    game->check(p1);
    game->allIn(p2);
    // EXPECT_THROW(game->call(p1), IllegalAction);
    game->allIn(p1);
    // game->allIn(p1);

    game->finish();

    EXPECT_EQ(game->stack(p1), 40);
    EXPECT_EQ(game->stack(p2), 10);
}
