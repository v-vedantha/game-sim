#include "TableCards.h"
#include <iostream>
#include <random>
#include <set>

TableCards::TableCards(std::vector<PlayerId> players) {
    // We can initialize empty hole cards for each player, and fill them in
    // during startGame because that lets users of this class potentially
    // customize how (or if) they want to shuffle the deck.
    for (const PlayerId &player : players) {
        holeCards[player] = HoleCards();
    }

    this->players = players;
}

void TableCards::dealPlayerCards() {
    for (const PlayerId &player : players) {
        holeCards[player].dealCards(deck);
    }
}

void TableCards::dealToStreet(Street street) {
    board.dealToStreet(deck, street);
}

void TableCards::dealToPlayer(PlayerId player, std::vector<Card> cards) {
    // Only used for testing/analysis purposes to deal specific cards to
    // players.
    holeCards[player].addCards(cards);
    deck.removeCards(cards);
}

void TableCards::dealToBoard(std::vector<Card> cards) {
    // Only used for testing/analysis purposes to deal specific cards to the
    // board.
    board.addCards(cards);
    deck.removeCards(cards);
}

std::vector<PlayerId>
TableCards::getWinners(const std::vector<PlayerId> &eligiblePlayers) {
    // This function expects to be called only once the board has reached the
    // river.

    // To get the winners of the hand we need to figure out how strong each
    // player is...
    std::unordered_map<PlayerId, Strength> strengths;

    for (const PlayerId &player : eligiblePlayers) {
        strengths[player] = holeCards[player].evaluate(board);
    }

    // ...and then just return the players who were the strongest, which is what
    // this mildly intricate loop does.
    // Note that all winners must be equally strong since if there are multiple
    // winners, they must have tied hand strenghts.
    std::vector<PlayerId> winners;
    for (const PlayerId &player : players) {
        if (winners.size() == 0) {
            // If there are no winners yet, this player by default is the
            // strongest player, and so is the winnner
            winners.push_back(player);
            continue;
        } else if (strengths[player] > strengths[winners[0]]) {
            // If this player is stronger than (any of) the winners, then it is
            // the strongest player so far.
            winners.clear();
            winners.push_back(player);
        } else if (strengths[player] == strengths[winners[0]]) {
            // If this player is a strong as one of (all of) the winners, then
            // it too is a winner.
            winners.push_back(player);
        }
    }

    return winners;
}

std::vector<PlayerId> TableCards::getWinners() { return getWinners(players); }

void TableCards::shuffleDeck(std::mt19937 &rng) { deck.shuffle(rng); }

WinningProbabilities TableCards::winningProbabilities(std::mt19937 &rng) {
    // Our strategy for figuring out the odds of each player winning the hand is
    // to run the board out to completion several times, and figure out how
    // often each player wins.
    WinningProbabilitiesBuilder winningProbabilitiesBuilder =
        WinningProbabilitiesBuilder(players);

    // Simualate a large number of runouts
    for (int i = 0; i < 1000; i++) {
        // Make a copy of the entire table cards state to make sure we don't
        // edit something accidentally.
        TableCards simulatedTableCards = *this;

        // Make sure each simulated game uses a different deck
        simulatedTableCards.shuffleDeck(rng);

        // Simulate the game to completion
        simulatedTableCards.dealToStreet(Street::RIVER);

        // Update the winners for this runout.
        std::vector<PlayerId> winners = simulatedTableCards.getWinners();
        winningProbabilitiesBuilder.addRunoutResult(winners);
    }

    return winningProbabilitiesBuilder.winningProbabilities();
}
