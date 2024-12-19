#include "Player.h"
#include "Game.h"

#include <cassert>
#include <memory>

Player::Player(PlayerId id, int chips) : id(id), chips(chips) {}

void Player::join(std::shared_ptr<Game> game) {
    this->game = game;
}

void Player::call() {
    assert(game);
    int cost = game->call(id);
    this->chips -= cost;
}

void Player::check() {
    assert(game);
    game->check(id);
}

void Player::raise(int amount) {
    game->raise(id, amount);
    this->chips -= amount;
}

void Player::reraise(int amount) {
    game->reraise(id, amount);
    this->chips -= amount;
}

void Player::allIn() {
    game->allIn(id, this->chips);
    this->chips = 0;
}

void Player::addChips(int amount) {
    this->chips += amount;
}

int Player::stack() {
    return chips;
}
