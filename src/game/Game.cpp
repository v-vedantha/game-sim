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

    // The table cards/bets interfaces require that you start the round before
    // using them.
    tableCards.shuffleDeck(rng);
    tableCards.dealPlayerCards();

    // The first betting round is always going to be the Preflop (even if
    // everyone checks, it is a betting round), so we can just start the
    // bettingRound in the constructor.
    street = Street::PREFLOP;
    bets.startRound(street);
}

void Game::dealToNextStreet() {
    // Make sure betting for the current round is complete before dealing out
    // the next street.
    assert(bets.bettingRoundComplete());

    street = nextStreet(street);
    tableCards.dealToStreet(street);

    // When dealing to the next street start betting for that street too.
    bets.startRound(street);
}

PlayerId Game::nextIdToAct() { return bets.nextIdToAct(); }

void Game::finish() {
    // Make sure betting is complete
    assert(bets.bettingRoundComplete());

    // The game can only finish on the river. Even if all players go all-in
    // preflop, the remaining cards must still be dealt out before showdown.
    assert(street == Street::RIVER);
    bets.distributeWinnings(tableCards);
}

void Game::check(PlayerId playerId) {
    assert(!bets.bettingRoundComplete());
    bets.check(playerId);
}

void Game::call(PlayerId playerId) {

    assert(!bets.bettingRoundComplete());
    bets.call(playerId);
}

void Game::raiseTo(PlayerId playerId, int amount) {
    assert(!bets.bettingRoundComplete());
    bets.raiseTo(playerId, amount);
}

void Game::allIn(PlayerId playerId) {
    assert(!bets.bettingRoundComplete());

    bets.allIn(playerId);
}

int Game::stack(PlayerId playerId) { return bets.stack(playerId); }
