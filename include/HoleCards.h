#pragma once
#include "Card.h"
#include "Board.h"
#include "Potential.h"
#include "Deck.h"
#include "Strength.h"

class HoleCards {
public:
    HoleCards();
    HoleCards(std::vector<Card> cards);

    void deal(std::vector<Card> cards);
    void deal(Card card);
    
    Strength evaluate(Board& board);

    Potential evaluatePotential(Board& board, Street& street, int randomSeed);
private:
    std::vector<Card> cards;
};
