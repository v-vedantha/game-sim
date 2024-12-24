#pragma once
#include <string>
#include <vector>

/**
 * @enum Suit
 * @brief Represents the suit of a playing card.
 *
 * - `HEARTS`: The hearts suit.
 * - `DIAMONDS`: The diamonds suit.
 * - `CLUBS`: The clubs suit.
 * - `SPADES`: The spades suit.
 * - `SUIT_UNSPECIFIED`: A placeholder for an unspecified suit.
 * When adding a new suit remember to update allSuits.
 */
enum class Suit { SUIT_UNSPECIFIED, HEARTS, DIAMONDS, CLUBS, SPADES };

/**
 * @enum Value
 * @brief Represents the rank of a playing card.
 *
 * - Numeric ranks: TWO to TEN.
 * - Face cards: JACK, QUEEN, KING.
 * - ACE: The highest or lowest card in some games.
 * - `VALUE_UNSPECIFIED`: A placeholder for an unspecified value.
 * When adding a new value remember to update allValues.
 */
enum class Value {
    VALUE_UNSPECIFIED,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};

/**
 * @brief A collection of all possible suits for a standard deck of cards.
 * Useful to iterate over all suits.
 */
extern const std::vector<Suit> allSuits;

/**
 * @brief A collection of all possible values for a standard deck of cards.
 * Useful to iterate over all values.
 */
extern const std::vector<Value> allValues;

/**
 * @class Card
 * @brief Represents a single playing card with a suit and value.
 */
class Card {
  public:
    /**
     * @brief The suit of the card.
     */
    Suit suit;

    /**
     * @brief The value of the card.
     */
    Value value;

    /**
     * @brief Constructs a card with a specified value and suit.
     *
     * @param value The rank of the card.
     * @param suit The suit of the card.
     */
    Card(Value value, Suit suit);

    /**
     * @brief Constructs a card with unspecified suit/value
     */
    Card();

    /**
     * @brief Compares two cards for equality.
     *
     * Two cards are equal if they have the same suit and value.
     *
     * @param other The other card to compare against.
     * @return True if the cards are equal, false otherwise.
     */
    bool operator==(const Card &other) const {
        return this->suit == other.suit && this->value == other.value;
    }

    friend std::ostream &operator<<(std::ostream &os, const Card &card);
};

std::ostream &operator<<(std::ostream &os, const Card &card);

std::ostream &operator<<(std::ostream &os, const Value &value);

std::ostream &operator<<(std::ostream &os, const Suit &suit);

/**
 * @struct CardComparator
 * @brief Returns true if lhs < rhs (useful for sorting in ascending order)
 */
struct CardComparator {
    /**
     * @brief Returns true if lhs < rhs
     */
    bool operator()(const Card &lhs, const Card &rhs) const;
};

/**
 * @struct CardReverseComparator
 * @brief Returns true if lhs > rhs (useful for sorting in descending order)
 */
struct CardReverseComparator {
    /**
     * @brief Returns true if lhs > rhs
     */
    bool operator()(const Card &c1, const Card &c2) const;
};

/**
 * @brief Compares two card values.
 *
 * @param v1 The first card value.
 * @param v2 The second card value.
 * @return A positive number if `v1` > `v2`, 0 if they are equal, or a negative
 * number if `v1` < `v2`.
 */
int compareValue(Value &v1, Value &v2);
