#include "Bets.h"
#include <cassert>
#include <iostream>

IllegalAction::IllegalAction(std::string message) { this->message = message; }

const char *IllegalAction::what() const throw() { return message.c_str(); }

Bets::Bets(std::vector<PlayerId> playerIds,
           std::shared_ptr<PlayersInHand> playersInHand)
    : pot(Pot(playerIds)) {
    this->playerIds = playerIds;
    this->currentStreet = Street::STREET_UNSPECIFIED;
    this->playersInHand = playersInHand;
}

void Bets::startRound(Street street) {
    currentStreet = street;
    bettingRounds[street] = std::make_unique<BettingRound>();
    pot.startRound(street);

    playersInHand->startNewBettingRound();
}

void Bets::call(PlayerId playerId) {
    assert(bettingRounds.find(currentStreet) != bettingRounds.end());
    int size =
        bettingRounds[currentStreet]->currentBet() - pot.amountPutIn(playerId);
    pot.add(playerId, size);

    playersInHand->advanceCurrentPlayer();
}

void Bets::check(PlayerId playerId) {

    if (pot.amountPutIn(playerId) !=
        bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Cannot check if we need to put money in.");
    }
    playersInHand->advanceCurrentPlayer();
}

void Bets::fold(PlayerId playerId) {
    playersInHand->removeCurrentPlayerFromHand();
}

int Bets::getCallingAmount() {
    return bettingRounds[currentStreet]->currentBet();
}
int Bets::getAmountPutIn(PlayerId playerId) {
    return pot.amountPutIn(playerId);
}

void Bets::raiseTo(PlayerId playerId, int amount) {
    if (amount < 2 * bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Must raise by atleast the current bet.");
    }
    bettingRounds[currentStreet]->raiseTo(amount);

    pot.add(playerId, amount - pot.amountPutIn(playerId));

    playersInHand->everyoneCanAct();
    playersInHand->advanceCurrentPlayer();
}

void Bets::allIn(PlayerId playerId, int amount) {
    if (amount > bettingRounds[currentStreet]->currentBet()) {
        playersInHand->everyoneCanAct();
    }
    pot.add(playerId, amount);
    bettingRounds[currentStreet]->allIn(pot.amountPutIn(playerId) + amount);

    playersInHand->removeCurrentPlayerFromBetting();
    playersInHand->advanceCurrentPlayer();
}

std::unique_ptr<std::unordered_map<PlayerId, int>>
Bets::getWinnings(TableCards &tableCards) {
    return pot.getWinnings(tableCards, *playersInHand);
}

bool Bets::bettingRoundComplete() { return playersInHand->isBettingOver(); }

PlayerId Bets::nextIdToAct() { return playersInHand->nextIdToAct(); }
