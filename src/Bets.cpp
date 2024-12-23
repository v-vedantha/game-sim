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
    this->playersInHand = playersInHand;

    // Initialize on an unspecified street. This is fine because users are meant
    // to call startRound before betting starts for each round.
    this->currentStreet = Street::STREET_UNSPECIFIED;
}

void Bets::startRound(Street street) {
    currentStreet = street;
    bettingRounds[street] = std::make_unique<BettingRound>();
    pot.startRound(street);

    playersInHand->startNewBettingRound();
}

void Bets::call(PlayerId playerId) {
    // Ensure that the player called startRound for this street.
    assert(bettingRounds.find(currentStreet) != bettingRounds.end());

    int callingCost = bettingRounds[currentStreet]->currentBet() -
                      pot.amountBet(currentStreet, playerId);
    if (callingCost > chipStacks->at(playerId)) {
        throw IllegalAction(
            "Cannot call a bet larger than chips left, must fold or allIn");
    }
    pot.add(playerId, callingCost);

    chipStacks->at(playerId) -= callingCost;
    playersInHand->advanceCurrentPlayer();
}

void Bets::check(PlayerId playerId) {

    // You can only check if you don't need to put in money to stay in the
    // round.
    if (pot.amountBet(currentStreet, playerId) !=
        bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Cannot check if we need to put money in.");
    }
    playersInHand->advanceCurrentPlayer();
}

void Bets::fold(PlayerId playerId) {
    playersInHand->removeCurrentPlayerFromHand();
}

void Bets::raiseTo(PlayerId playerId, int amount) {
    // You must raise to atleast 2x the current bet.
    if (amount < 2 * bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Must raise by atleast the current bet.");
    }
    int raiseCost = amount - pot.amountBet(currentStreet, playerId);
    if (raiseCost > chipStacks->at(playerId)) {
        throw IllegalAction("Don't have enough chips to perform this raise");
    }
    bettingRounds[currentStreet]->raiseTo(amount);

    pot.add(playerId, raiseCost);
    chipStacks->at(playerId) -= raiseCost;

    playersInHand->everyoneCanAct();
    playersInHand->advanceCurrentPlayer();
}

void Bets::allIn(PlayerId playerId) {
    int remainingChips = chipStacks->at(playerId);
    int allInTotalChips =
        pot.amountBet(currentStreet, playerId) + remainingChips;
    if (allInTotalChips > bettingRounds[currentStreet]->currentBet()) {
        playersInHand->everyoneCanAct();
    }
    pot.add(playerId, remainingChips);
    bettingRounds[currentStreet]->allInTo(allInTotalChips);
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
