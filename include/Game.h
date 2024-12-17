#pragma once
#include "Card.h"
#include "HoleCards.h"
#include "Board.h"
#include "Deck.h"
#include "PlayerId.h"
#include "WinningProbabilities.h"

class Game {
public:
    Game(std::vector<PlayerId> players);

    // For testing, deals specific cards to each player
    void dealToPlayer(PlayerId player, std::vector<Card> cards);
    // For testing, deals specific cards to the board 
    void dealToBoard(std::vector<Card> cards);

    void dealToBoard();

    void shuffleDeck();
    void shuffleDeck(std::mt19937& rng);

    WinningProbabilities winningProbabilities(int randomSeed);    
    std::vector<PlayerId> getWinners();

private:
    std::vector<PlayerId> players;
    std::unordered_map<PlayerId, HoleCards> holeCards;

    Board board;
    Deck deck;
};

