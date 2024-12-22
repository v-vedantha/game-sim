#pragma once
#include "Board.h"
#include "PlayerId.h"
#include "PlayersInHand.h"
#include "TableCards.h"
#include <map>
#include <memory>
#include <vector>

class Pot {

  public:
    Pot(std::vector<PlayerId> playerIds);

    void startRound(Street street);
    void add(PlayerId playerId, int amount);
    int amountPutIn(PlayerId playerId);

    std::unique_ptr<std::unordered_map<PlayerId, int>>
    getWinnings(TableCards &tableCards, PlayersInHand &playersInHand);

  private:
    Street street;
    std::unordered_map<Street, std::unordered_map<PlayerId, int>> amountsPutIn;
};
