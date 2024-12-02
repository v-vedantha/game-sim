#pragma once
#include <string>

enum class Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Value {
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

class Card {
public:
    Suit suit;
    Value value;
    Card(Value value, Suit suit);

    bool operator==(const Card& other) const {
        return this->suit == other.suit && this->value == other.value;
    }

    bool operator<(const Card& other) const {
        return this->value < other.value;
    }

    std::string toString() const;
};
