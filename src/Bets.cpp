#include "Bets.h"
#include <cassert>
#include <iostream>

Bets::Bets(std::vector<PlayerId> playerIds, std::shared_ptr<PlayersInHand> playersInHand) : pot(Pot(playerIds)) {
    this->playerIds = playerIds;
    this->currentStreet = Street::STREET_UNSPECIFIED;
    this->playersInHand = playersInHand;
}

void Bets::startRound(Street street) {
    currentStreet = street;
    bettingRounds[street] = std::make_unique<BettingRound>();

    playersInHand->startNewBettingRound();
}


int Bets::call(PlayerId playerId) {
    assert(bettingRounds.find(currentStreet) != bettingRounds.end());
    int size = bettingRounds[currentStreet]->currentBet();
    pot.add(playerId, size);

    playersInHand->advanceCurrentPlayer();
    return size;
}

void Bets::check(PlayerId playerId) {
    playersInHand->advanceCurrentPlayer();
}

void Bets::fold(PlayerId playerId) {
    playersInHand->removeCurrentPlayerFromHand();
}

void Bets::raise(PlayerId playerId, int amount) {
    bettingRounds[currentStreet]->raiseTo(amount);

    pot.add(playerId, amount);

    playersInHand->everyoneCanAct();
    playersInHand->advanceCurrentPlayer();
}

void Bets::reraise(PlayerId playerId, int amount) {
    assert(amount > bettingRounds[currentStreet]->currentBet());
    bettingRounds[currentStreet]->raiseTo(amount);

    pot.add(playerId, amount);

    playersInHand->everyoneCanAct();
    playersInHand->advanceCurrentPlayer();
}


void Bets::allIn(PlayerId playerId, int amount) {
    if (amount > bettingRounds[currentStreet]->currentBet()) {
        playersInHand->everyoneCanAct();
    }
    pot.add(playerId, amount);
    bettingRounds[currentStreet]->allIn(amount);

    playersInHand->removeCurrentPlayerFromBetting();
    playersInHand->advanceCurrentPlayer();
}

std::unique_ptr<std::unordered_map<PlayerId, int>> Bets::getWinnings(TableCards& tableCards) {
    return pot.getWinnings(tableCards, *playersInHand);
}


bool Bets::bettingRoundComplete() {
    return playersInHand->isBettingOver();
}


PlayerId Bets::nextIdToAct() {
    return playersInHand->nextIdToAct();
}
