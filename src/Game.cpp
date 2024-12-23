#include "Game.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

Game::Game(std::vector<PlayerId> playerIds,
           std::unique_ptr<std::unordered_map<PlayerId, int>> chips,
           std::mt19937 &rng)
    : tableCards(playerIds),
      playersInHand(std::make_shared<PlayersInHand>(playerIds)),
      bets(playerIds, playersInHand, std::move(chips)) {

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
    bets.distributeWinnings(tableCards);
}

void Game::check(PlayerId playerId) { bets.check(playerId); }

void Game::call(PlayerId playerId) { bets.call(playerId); }

void Game::raiseTo(PlayerId playerId, int amount) {
    bets.raiseTo(playerId, amount);
}

void Game::allIn(PlayerId playerId) { bets.allIn(playerId); }

int Game::stack(PlayerId playerId) { return bets.stack(playerId); }
