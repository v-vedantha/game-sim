#include "Game.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

Game::Game(std::vector<PlayerId> playerIds,
           std::shared_ptr<std::unordered_map<PlayerId, int>> chips,
           std::mt19937 &rng)
    : tableCards(playerIds),
      playersInHand(std::make_shared<PlayersInHand>(playerIds)),
      bets(playerIds, playersInHand) {

    this->chipStacks = chips;
    tableCards.startGame(rng);
    street = Street::PREFLOP;
    bets.startRound(street);
}

void Game::dealToNextStreet() {
    assert(bets.bettingRoundComplete());

    street = nextStreet(street);
    bets.startRound(street);
    tableCards.dealToStreet(street);
}

PlayerId Game::nextIdToAct() { return bets.nextIdToAct(); }

void Game::finish() {
    assert(bets.bettingRoundComplete());
    assert(street == Street::RIVER);
    std::unique_ptr<std::unordered_map<PlayerId, int>> winnings =
        bets.getWinnings(tableCards);

    // Update the chip stacks with the winnings
    for (auto it = winnings->begin(); it != winnings->end(); it++) {
        chipStacks->at(it->first) += it->second;
    }
}

void Game::check(PlayerId playerId) { bets.check(playerId); }

void Game::call(PlayerId playerId) {
    int chipsCost = bets.getCallingAmount() - bets.getAmountPutIn(playerId);
    if (bets.getCallingAmount() - bets.getAmountPutIn(playerId) >
        chipStacks->at(playerId)) {
        throw IllegalAction(
            "Cannot call a bet larger than chips left, must fold or allIn");
    }

    bets.call(playerId);
    chipStacks->at(playerId) -= chipsCost;
}

void Game::raiseTo(PlayerId playerId, int amount) {
    int amountAdded = amount - bets.getAmountPutIn(playerId);
    if (amount - bets.getAmountPutIn(playerId) > chipStacks->at(playerId)) {
        throw IllegalAction("Don't have enough chips to perform this raise");
    }

    // Can also throw.
    bets.raiseTo(playerId, amount);

    chipStacks->at(playerId) -= amountAdded;
}

void Game::allIn(PlayerId playerId) {
    bets.allIn(playerId, chipStacks->at(playerId));
    chipStacks->at(playerId) = 0;
}

int Game::stack(PlayerId playerId) { return chipStacks->at(playerId); }
