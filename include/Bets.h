#pragma once

#include "TableCards.h"
#include "PlayerId.h"
#include "PlayersInHand.h"
#include "BettingRound.h"
#include "Pot.h"

#include <memory>
#include <vector>
#include <map>


class Bets {

public:
    Bets(std::vector<PlayerId> playerIds, std::shared_ptr<PlayersInHand> playersInHand);
    void startRound(Street street);

    PlayerId nextIdToAct();

    int call(PlayerId playerId);
    void check(PlayerId playerId);
    void fold(PlayerId playerId);
    void raise(PlayerId playerId, int amount);
    void reraise(PlayerId playerId, int amount);
    void allIn(PlayerId playerId, int amount);

    bool bettingRoundComplete();

    std::unique_ptr<std::unordered_map<PlayerId, int>> getWinnings(TableCards& tableCards);

private:
    // Owned by the Game.
    std::shared_ptr<PlayersInHand> playersInHand;

    std::vector<PlayerId> playerIds;
    Street currentStreet;
    std::unordered_map<Street, std::unique_ptr<BettingRound>> bettingRounds;
    
    Pot pot;
};
