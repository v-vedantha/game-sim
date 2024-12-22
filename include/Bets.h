#pragma once

#include "BettingRound.h"
#include "PlayerId.h"
#include "PlayersInHand.h"
#include "Pot.h"
#include "TableCards.h"

#include <map>
#include <memory>
#include <vector>

class IllegalAction : public std::exception {
    std::string message;

  public:
    IllegalAction(std::string message);

    const char *what() const throw();
};

class Bets {

  public:
    Bets(std::vector<PlayerId> playerIds,
         std::shared_ptr<PlayersInHand> playersInHand);
    void startRound(Street street);

    PlayerId nextIdToAct();

    void call(PlayerId playerId);
    void check(PlayerId playerId);
    void fold(PlayerId playerId);
    void raiseTo(PlayerId playerId, int amount);
    void allIn(PlayerId playerId, int amount);

    // Used by the game to validate wether certain bets are even legal
    int getCallingAmount();
    int getAmountPutIn(PlayerId playerId);

    bool bettingRoundComplete();

    std::unique_ptr<std::unordered_map<PlayerId, int>>
    getWinnings(TableCards &tableCards);

  private:
    // Owned by the Game.
    std::shared_ptr<PlayersInHand> playersInHand;

    std::vector<PlayerId> playerIds;
    Street currentStreet;
    std::unordered_map<Street, std::unique_ptr<BettingRound>> bettingRounds;

    Pot pot;
};
