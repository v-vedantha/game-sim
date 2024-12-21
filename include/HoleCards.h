#pragma once
#include "Card.h"
#include "Board.h"
#include "Potential.h"
#include "Deck.h"
#include "Strength.h"

// HoleCards represents the two cards each player has.

class HoleCards {
public:
    HoleCards();
    HoleCards(std::vector<Card> cards);

    void addCards(std::vector<Card> cards);
    void addCard(Card card);

    void dealCards(Deck& deck);

    Strength evaluate(Board& board);

    Potential evaluatePotential(Board& board, Street& street, std::mt19937& rng);
private:
    std::vector<Card> cards;
};
