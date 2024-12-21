#pragma once
#include "Card.h"
#include "HoleCards.h"
#include "Board.h"
#include "Deck.h"
#include "PlayerId.h"
#include "WinningProbabilities.h"

class TableCards {
public:
    TableCards(std::vector<PlayerId> players);

    void startGame(std::mt19937& rng);

    void dealToStreet(Street street);

    void shuffleDeck(std::mt19937& rng);

    WinningProbabilities winningProbabilities(std::mt19937& rng);    
    std::vector<PlayerId> getWinners();
    std::vector<PlayerId> getWinners(const std::vector<PlayerId>& eligiblePlayers);

    // For testing
    void dealToPlayer(PlayerId player, std::vector<Card> cards);
    void dealToBoard(std::vector<Card> cards);
    void dealToBoard();
private:
    std::vector<PlayerId> players;
    std::unordered_map<PlayerId, HoleCards> holeCards;

    Board board;
    Deck deck;
};

