#pragma once
#include "Card.h"
#include <list>
#include <random>

class Deck {
public:
    Deck();

    void removeCards(std::vector<Card> cards);
    void removeCard(Card cards);
    Card deal();
    void shuffle();
    void shuffle(std::mt19937& rng);

private:
    std::list<Card> cards;
};
