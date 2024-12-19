#include "Game.h"
#include "Player.h"
#include <memory>
#include <cassert>
#include <iostream>
#include <vector>

void GameBuilder::addPlayer(std::shared_ptr<Player> player) {
    this->players.push_back(player);
}

std::shared_ptr<Game> GameBuilder::build() {
    std::shared_ptr<Game> game = std::make_shared<Game>(players);
    for (std::weak_ptr<Player>& player : players) {
        player.lock()->join(game);
    }

    return game;
}


std::vector<PlayerId> getPlayerIds(std::vector<std::weak_ptr<Player>> players) {
    
    std::vector<PlayerId> playerIds;
    for (std::weak_ptr<Player> player : players) {
        playerIds.push_back(player.lock()->id);
    }

    return playerIds;

}

Game::Game(std::vector<std::weak_ptr<Player>> players): tableCards(getPlayerIds(players)), playersInHand(std::make_shared<PlayersInHand>(getPlayerIds(players))),
       bets(getPlayerIds(players), playersInHand) {

    for (auto player : players) {
        playersById[player.lock()->id] = player;
    }

    tableCards.startGame();
    street = Street::PREFLOP;
    bets.startRound(street);

}


void Game::dealToNextStreet() {
    assert(bets.bettingRoundComplete());

    street = nextStreet(street);
    bets.startRound(street);
    tableCards.dealToStreet(street);
}

PlayerId Game::nextIdToAct() {
    return bets.nextIdToAct();
}

void Game::finish() {
    assert(bets.bettingRoundComplete());
    assert(street == Street::RIVER);
    std::unique_ptr<std::unordered_map<PlayerId, int>> winnings = bets.getWinnings(tableCards);

    for (auto it = winnings->begin(); it != winnings->end(); it++) { 

        
        std::shared_ptr<Player> player = playersById[it->first].lock();
        player->addChips(it->second);
    }
}

void Game::check(PlayerId playerId) {
    bets.check(playerId);
}

int Game::call(PlayerId playerId) {
    return bets.call(playerId);
}

void Game::raise(PlayerId playerId, int amount) {
    bets.raise(playerId, amount);
}
void Game::reraise(PlayerId playerId, int amount) {
    bets.reraise(playerId, amount);
}

void Game::allIn(PlayerId playerId, int amount) {
    bets.allIn(playerId, amount);
}




