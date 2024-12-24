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

    // It does not matter which street we initialize currentStreet to because
    // startRound must always be called before betting starts.
    this->currentStreet = Street::STREET_UNSPECIFIED;
}

void Bets::startRound(Street street) {
    currentStreet = street;
    bettingRounds[street] = std::make_unique<BettingRound>();
    pot.startRound(street);
    playersInHand->startNewBettingRound();
}

void Bets::call(PlayerId playerId) {
    // Ensure that startRound has been called.
    assert(bettingRounds.find(currentStreet) != bettingRounds.end());

    // The cost to call is the bet minus the amount you've already contributed.
    int callingCost = bettingRounds[currentStreet]->currentBet() -
                      pot.amountBet(currentStreet, playerId);
    if (callingCost > chipStacks->at(playerId)) {
        throw IllegalAction(
            "Cannot call a bet larger than chips left, must fold or allIn");
    }

    // Move the chips from the players stack to the pot.
    pot.add(playerId, callingCost);
    chipStacks->at(playerId) -= callingCost;

    // It is now the next players turn.
    playersInHand->advanceCurrentPlayer();
}

void Bets::check(PlayerId playerId) {

    // Checking is only allowed when you don't need to put in money to match the
    // current bet.
    if (pot.amountBet(currentStreet, playerId) !=
        bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Cannot check if we need to put money in.");
    }

    // It is now the next players turn.
    playersInHand->advanceCurrentPlayer();
}

void Bets::fold(PlayerId playerId) {
    // Folded players are no longer in the hand.
    playersInHand->removeCurrentPlayerFromHand();
}

void Bets::raiseTo(PlayerId playerId, int amount) {
    // You must raise to atleast 2x the current bet.
    if (amount < 2 * bettingRounds[currentStreet]->currentBet()) {
        throw IllegalAction("Must raise by atleast the current bet.");
    }

    // The cost of the raise is the amount you're raising to minus the amount
    // you've already put into the pot.
    int raiseCost = amount - pot.amountBet(currentStreet, playerId);
    if (raiseCost > chipStacks->at(playerId)) {
        throw IllegalAction("Don't have enough chips to perform this raise");
    }
    bettingRounds[currentStreet]->raiseTo(amount);

    // Move the chips from the players chipstacks into the pot.
    pot.add(playerId, raiseCost);
    chipStacks->at(playerId) -= raiseCost;

    // Raising reopens action for everyone...
    playersInHand->everyoneCanAct();
    // ... except the player who raised.
    playersInHand->advanceCurrentPlayer();
}

void Bets::allIn(PlayerId playerId) {
    int remainingChips = chipStacks->at(playerId);
    int allInTotalChips =
        pot.amountBet(currentStreet, playerId) + remainingChips;

    // If going all in also happens to be a raise, then action reopens.
    if (allInTotalChips > bettingRounds[currentStreet]->currentBet()) {
        playersInHand->everyoneCanAct();
    }
    bettingRounds[currentStreet]->allInTo(allInTotalChips);

    // Move the chips into the pot.
    pot.add(playerId, remainingChips);
    chipStacks->at(playerId) = 0;

    // Once a player goes all in, they cannot be involved in any more betting
    // since they have no more chips remaining. They are still in the hand
    // though and can win money at showdown.
    playersInHand->removeCurrentPlayerFromBetting();
    playersInHand->advanceCurrentPlayer();
}

void Bets::distributeWinnings(TableCards &tableCards) {
    auto winnings = pot.getWinnings(tableCards, *playersInHand);

    // Distribute winnings directly onto the chipstacks of each player.
    for (auto it = winnings->begin(); it != winnings->end(); it++) {
        chipStacks->at(it->first) += it->second;
    }
}

int Bets::stack(PlayerId playerId) { return chipStacks->at(playerId); }

bool Bets::bettingRoundComplete() { return playersInHand->isBettingOver(); }

PlayerId Bets::nextIdToAct() { return playersInHand->nextIdToAct(); }
