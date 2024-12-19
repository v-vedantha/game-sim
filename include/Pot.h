#pragma once
#include "PlayerId.h"
#include "TableCards.h"
#include "PlayersInHand.h"
#include <memory>
#include <map>
#include <vector>

class Pot {


public:
    Pot(std::vector<PlayerId> playerIds);

    void add(PlayerId playerId, int amount);

    std::unique_ptr<std::unordered_map<PlayerId, int>> getWinnings(TableCards& tableCards, PlayersInHand& playersInHand);

private:
    bool isEmpty();
    std::unordered_map<PlayerId, int> amountsPutIn;
};
