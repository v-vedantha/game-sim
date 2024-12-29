#pragma once
#include "Card.h"
#include <list>
#include <random>

/**
 * @class Deck
 * @brief Represent a deck of cards.
 *
 */
class Deck {
  public:
    /**
     * @brief Construct a 52-card deck.
     *
     */
    Deck();

    /**
     * @brief Remove the given cards from the deck.
     *
     * @param cards
     */
    void removeCards(std::vector<Card> cards);

    /**
     * @brief  Remove the given card from the deck.
     *
     * @param cards
     */
    void removeCard(Card cards);

    /**
     * @brief Deals a card from the deck, this card is then removed
     *
     * @return Card The card dealt from the deck
     */
    Card deal();
    void shuffle(std::mt19937 &rng);

  private:
    /**
     * @brief The cards remaining in the deck. Uses a list instead of a vector
     * so elements can be removed from arbitrary locations
     *
     */
    std::list<Card> cards;
};
