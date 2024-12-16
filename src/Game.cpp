#include "Game.h"
#include <set>
#include <iostream>
#include <random>

Game::Game(std::vector<PlayerId> players) {
    for (const PlayerId& player : players) {
        holeCards[player] = HoleCards();
    }

    this->players = players;
}

void Game::dealToPlayer(PlayerId player, std::vector<Card> cards) {
    holeCards[player].addCards(cards);
    deck.removeCards(cards);
}

void Game::dealToBoard(std::vector<Card> cards) {
    board.addCards(cards);
    deck.removeCards(cards);
}

void Game::dealToBoard() {
    Card card = deck.deal();
    board.addCard(card);
}


std::vector<PlayerId> Game::getWinners() {
    std::unordered_map<PlayerId, Strength> strengths;

    for (const PlayerId& player : players) {
        strengths[player] = holeCards[player].evaluate(board);
    }

    std::vector<PlayerId> winners;
    for (const PlayerId& player : players) {
        if (winners.size() == 0) {
            winners.push_back(player);
            continue;
        } else if (strengths[player] > strengths[winners[0]]) {
            winners.clear();
            winners.push_back(player);
        } else if (strengths[player] == strengths[winners[0]]) {
            winners.push_back(player);
        }
    }

    return winners;
}

void Game::shuffleDeck(std::mt19937& rng) {
    deck.shuffle(rng);
}

void Game::shuffleDeck() {
    deck.shuffle();
}

WinningProbabilities Game::winningProbabilities(int randomSeed) {
    WinningProbabilitiesBuilder winningProbabilitiesBuilder = WinningProbabilitiesBuilder(players);

    std::mt19937 g(randomSeed);
    // Simualate a large number of runouts
    for (int i = 0; i < 1000; i++) {
        // Is this even the right approach? Make a bunch of copies of the game?
        // alternatives, run the board out several times
        // costs -> then I need to make a function like getWinners(board)
        // which is odd or board.getwinners(players) which is also not natural
        Game simulatedGame = *this;

        // Make sure each simulated game uses a different deck
        simulatedGame.shuffleDeck(g);

        // Make a method called finished?
        // Make a method called finish?
        while (simulatedGame.board.size() < 5) {
            simulatedGame.dealToBoard();
        }

        std::vector<PlayerId> winners = simulatedGame.getWinners();
        winningProbabilitiesBuilder.addRunoutResult(winners);
    }

    return winningProbabilitiesBuilder.winningProbabilities();
}



