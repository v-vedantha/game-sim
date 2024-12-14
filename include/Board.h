#pragma once
#include "Card.h"
#include "Deck.h"
#include "Strength.h"

#include <vector>
#include <map>

enum class Street {STREET_UNSPECIFIED, FLOP, TURN, RIVER};

class Board {
    std::vector<Card> cards;

public:
    Board();
    Board(std::vector<Card> cards);

    void deal(Card card);
    void deal(std::vector<Card> cards);

    void dealToStreet(Deck& deck, Street& street);
    int size();

    std::vector<Card> getCards();

    Strength strength();
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

std::ostream& operator<<(std::ostream& os, const Board& board);
