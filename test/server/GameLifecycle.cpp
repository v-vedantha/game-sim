#include "Server.h"

using namespace server;

TEST(GameLifecycle, StartGame) {

    // Create a game
    auto response = makeRequest(CreateGame());

    GameInfo gameInfo = GameInfo(response);

    GameId gameId = gameInfo.gameId();

    // Cannot start the game until 2 people have joined
    PlayerId p1 = PlayerId("p1");
    PlayerId p2 = PlayerId("p2");
    makeRequest(JoinGame(p1));
    makeRequest(JoinGame(p2));

    makeRequest(StartGame(p1));

    // TBD
    makeRequest(EndGame());
}
