#pragma once
#include "Card.h"
#include "Deck.h"
#include "Strength.h"

#include <vector>
#include <map>

// Streets are the common term to represent the number of cards on the board.
// Initially (Preflop), there are zero cards, then after the Flop there are 3
// then after the turn there are 4, and the river 5.
enum class Street {STREET_UNSPECIFIED, FLOP, TURN, RIVER};

class Board {
    std::vector<Card> cards;

public:
    Board();
    Board(std::vector<Card> cards);

    void addCard(Card card);
    void addCards(std::vector<Card> cards);

    void dealToStreet(Deck& deck, Street& street);
    int size();

    std::vector<Card> getCards();

    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
