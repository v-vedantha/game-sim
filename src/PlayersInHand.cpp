#include "PlayersInHand.h"
#include <iostream>

PlayersInHand::PlayersInHand(std::vector<PlayerId> playerIds) {
    this->playersInHand = playerIds;
    for (PlayerId playerId : playerIds) {
        playersWhoCanBet.insert(playerId);
    }
}

void PlayersInHand::startNewBettingRound() {
    lastPlayer = playersInHand.size() - 1;
    currentPlayer = 0;
    m_isBettingOver = false;
}

void PlayersInHand::removeCurrentPlayerFromBetting() {
    playersWhoCanBet.erase(playersInHand[currentPlayer]);
}

void PlayersInHand::advanceCurrentPlayer() {
    if (currentPlayer == lastPlayer) {
        m_isBettingOver = true;
    }
    do {
        currentPlayer = (currentPlayer + 1) % playersInHand.size();
    } while (playersWhoCanBet.find(playersInHand[currentPlayer]) == playersWhoCanBet.end());
}

void PlayersInHand::everyoneCanAct() {
    lastPlayer = currentPlayer - 1;
    if (lastPlayer < 0) {
        lastPlayer = playersInHand.size() - 1;
    }
}

PlayerId PlayersInHand::nextIdToAct() {
    return playersInHand[currentPlayer];
}

void PlayersInHand::removeCurrentPlayerFromHand() {
    playersInHand.erase(playersInHand.begin() + currentPlayer);
}

std::vector<PlayerId> PlayersInHand::getPlayersStillInHand() {
    return playersInHand;
}

bool PlayersInHand::isBettingOver() {
    return m_isBettingOver;
}

