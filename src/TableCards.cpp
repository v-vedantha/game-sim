#include "TableCards.h"
#include <iostream>
#include <random>
#include <set>

TableCards::TableCards(std::vector<PlayerId> players) {
    for (const PlayerId &player : players) {
        holeCards[player] = HoleCards();
    }

    this->players = players;
}

void TableCards::startGame(std::mt19937 &rng) {
    shuffleDeck(rng);
    for (const PlayerId &player : players) {
        holeCards[player].dealCards(deck);
    }
}

void TableCards::dealToStreet(Street street) {
    board.dealToStreet(deck, street);
}

void TableCards::dealToPlayer(PlayerId player, std::vector<Card> cards) {
    holeCards[player].addCards(cards);
    deck.removeCards(cards);
}

void TableCards::dealToBoard(std::vector<Card> cards) {
    board.addCards(cards);
    deck.removeCards(cards);
}

std::vector<PlayerId>
TableCards::getWinners(const std::vector<PlayerId> &eligiblePlayers) {
    std::unordered_map<PlayerId, Strength> strengths;

    for (const PlayerId &player : eligiblePlayers) {
        strengths[player] = holeCards[player].evaluate(board);
    }

    std::vector<PlayerId> winners;
    for (const PlayerId &player : players) {
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

std::vector<PlayerId> TableCards::getWinners() { return getWinners(players); }

void TableCards::shuffleDeck(std::mt19937 &rng) { deck.shuffle(rng); }

WinningProbabilities TableCards::winningProbabilities(std::mt19937 &rng) {
    WinningProbabilitiesBuilder winningProbabilitiesBuilder =
        WinningProbabilitiesBuilder(players);

    // Simualate a large number of runouts
    for (int i = 0; i < 1000; i++) {
        TableCards simulatedTableCards = *this;

        // Make sure each simulated game uses a different deck
        simulatedTableCards.shuffleDeck(rng);

        simulatedTableCards.dealToStreet(Street::RIVER);

        std::vector<PlayerId> winners = simulatedTableCards.getWinners();
        winningProbabilitiesBuilder.addRunoutResult(winners);
    }

    return winningProbabilitiesBuilder.winningProbabilities();
}
