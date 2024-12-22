#pragma once
#include "Card.h"
#include "Strength.h"
#include <set>
#include <vector>

// In poker you compare the best 5-card-hand each player has.
// A hand is a wrapper around 5-cards that lets you evaluate properties
// of the hand.

struct HasFlush {
    bool isFlush;
    std::array<Value, 5> kickers;
};

struct HasStraight {
    bool isStraight;
    Value highCard;
};

struct HasQuads {
    bool isQuads;
    Value quadsCard;
    Value kicker;
};

struct HasFullHouse {
    bool isFullHouse;
    Value threeOfAKind;
    Value pair;
};

struct HasThreeOfAKind {
    bool isThreeOfAKind;
    Value threeOfAKind;
    std::array<Value, 2> kickers;
};

struct HasTwoPair {
    bool isTwoPair;
    // Sorted high to low
    std::array<Value, 2> pairs;
    Value kicker;
};

struct HasPair {
    bool isPair;
    Value pair;
    std::array<Value, 3> kickers;
};

class Hand {
  private:
    /**
     * @brief The cards in the hand. Stored in descending order of value.
     *
     */
    std::array<Card, 5> cards;

    /**
     * @brief Populated with each value in the the hand. Useful for checking if
     * you have a four of a kind for example.
     *
     */
    std::multiset<Value> values;

    HasFlush hasFlush();
    HasStraight hasStraight();
    HasQuads hasQuads();
    HasFullHouse hasFullHouse();
    HasThreeOfAKind hasThreeOfAKind();
    HasTwoPair hasTwoPair();
    HasPair hasPair();

    /**
     * @brief Sets the `cards` field. Sorts the cards.
     *
     * @param cards
     */
    void setCards(std::array<Card, 5> cards);

  public:
    /**
     * @brief Construct a hand with 5 cards
     *
     * @param cards
     */
    Hand(std::array<Card, 5> cards);

    /**
     * @brief Construct a hand with 5 cards. Expects the vector to have
     * length 5.
     *
     * @param cards
     * @throw A runtime exception if vector is not length 5.
     */
    Hand(std::vector<Card> cards);

    /**
     * @brief Determines the strength of this hand, like quads, full-house, and
     * returns a Strength object which can be used to compare between hands.
     *
     * @return Strength The strength of this hand.
     */
    Strength evaluate();
};
