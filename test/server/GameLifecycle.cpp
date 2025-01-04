#include "Games.h"
#include "Server.h"
#include <gtest/gtest.h>

TEST(GameLifecycle, CreateGame) {
    Games games;

    // Create a game
    auto response = handleCreateGame(games);

    std::cout << *response << std::endl;
}
