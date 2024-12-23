#include "Bets.h"
#include <cassert>
#include <iostream>

IllegalAction::IllegalAction(std::string message) { this->message = message; }

const char *IllegalAction::what() const throw() { return message.c_str(); }

Bets::Bets(std::vector<PlayerId> playerIds,
           std::shared_ptr<PlayersInHand> playersInHand,
           std::unique_ptr<std::unordered_map<PlayerId, int>> chips)
    : pot(Pot(playerIds)) {
    this->playerIds = playerIds;
    this->chipStacks = std::move(chips);

    // Initialize on an unspecified street. This is fine because users are meant
    // to call startRound before betting starts for each round.
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
    if (size > chipStacks->at(playerId)) {
        throw IllegalAction(
            "Cannot call a bet larger than chips left, must fold or allIn");
    }
    pot.add(playerId, size);

    chipStacks->at(playerId) -= size;
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

void Bets::raiseTo(PlayerId playerId, int amount) {
    if (amount < 2 * bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Must raise by atleast the current bet.");
    }
    int amountAdded = amount - pot.amountPutIn(playerId);
    if (amountAdded > chipStacks->at(playerId)) {
        throw IllegalAction("Don't have enough chips to perform this raise");
    }
    bettingRounds[currentStreet]->raiseTo(amount);

    pot.add(playerId, amountAdded);
    chipStacks->at(playerId) -= amountAdded;

    playersInHand->everyoneCanAct();
    playersInHand->advanceCurrentPlayer();
}

void Bets::allIn(PlayerId playerId) {
    int amount = chipStacks->at(playerId);
    if (amount > bettingRounds[currentStreet]->currentBet()) {
        playersInHand->everyoneCanAct();
    }
    pot.add(playerId, amount);
    bettingRounds[currentStreet]->allInTo(pot.amountPutIn(playerId) + amount);
    chipStacks->at(playerId) = 0;

    playersInHand->removeCurrentPlayerFromBetting();
    playersInHand->advanceCurrentPlayer();
}

void Bets::distributeWinnings(TableCards &tableCards) {
    auto winnings = pot.getWinnings(tableCards, *playersInHand);
    for (auto it = winnings->begin(); it != winnings->end(); it++) {
        chipStacks->at(it->first) += it->second;
    }
}

int Bets::stack(PlayerId playerId) { return chipStacks->at(playerId); }

bool Bets::bettingRoundComplete() { return playersInHand->isBettingOver(); }

PlayerId Bets::nextIdToAct() { return playersInHand->nextIdToAct(); }
