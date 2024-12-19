#pragma once
#include "PlayerId.h"
#include "TableCards.h"
#include <vector>
#include <unordered_set>


class PlayersInHand {

public:
    PlayersInHand(std::vector<PlayerId> playerIds);

    void advanceCurrentPlayer();

    void removeCurrentPlayerFromHand();

    void everyoneCanAct();

    void removeCurrentPlayerFromBetting();

    void startNewBettingRound();

    PlayerId nextIdToAct();

    std::vector<PlayerId> getPlayersStillInHand();

    bool isBettingOver();

private:

    std::vector<PlayerId> playersInHand;

    std::unordered_set<PlayerId> playersWhoCanBet;
    int currentPlayer;
    int lastPlayer;

    bool m_isBettingOver;
};
