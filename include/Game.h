#pragma once
#include "Bets.h"
#include "PlayerId.h"
#include "TableCards.h"
#include <map>
#include <memory>

class Player;

class Game {

  public:
    void finish();

    void dealToNextStreet();

    PlayerId nextIdToAct();

    // Should always match nextIdToAct so technically unnecessary
    // but it is useful to be confident that the game is in a consistent state.
    void check(PlayerId playerId);
    void call(PlayerId playerId);
    void raiseTo(PlayerId playerId, int amount);
    void allIn(PlayerId playerId);

    int stack(PlayerId playerId);

    Game(std::vector<PlayerId> playerIds,
         std::shared_ptr<std::unordered_map<PlayerId, int>> chips,
         std::mt19937 &rng);

  private:
    std::vector<std::weak_ptr<PlayerId>> players;

    TableCards tableCards;

    // Game owns playersInHand. Bets stores an additional reference
    std::shared_ptr<PlayersInHand> playersInHand;

    // Game owns, bets stores additional reference.
    std::shared_ptr<std::unordered_map<PlayerId, int>> chipStacks;

    Bets bets;

    Street street;
};
