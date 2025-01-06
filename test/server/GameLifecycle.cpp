#include "Rooms.h"
#include "Server.h"
#include <gtest/gtest.h>

TEST(GameLifecycle, CreateGame) {
    Rooms rooms;

    // Create a game
    auto response = handleCreateRoom(rooms);

    std::cout << *response << std::endl;
}
