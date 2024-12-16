#pragma once
#include <string>
#include <vector>

enum class Suit {
    SUIT_UNSPECIFIED,
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};


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


extern const std::vector<Suit> allSuits; 
extern const std::vector<Value> allValues;

class Card {
public:
    Suit suit;
    Value value;

    Card(Value value, Suit suit);
    Card();

    bool operator==(const Card& other) const {
        return this->suit == other.suit && this->value == other.value;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card);

};

std::ostream& operator<<(std::ostream& os, const Card& card);
std::ostream& operator<<(std::ostream& os, const Value& value);
std::ostream& operator<<(std::ostream& os, const Suit& suit);

struct CardComparator {
    bool operator()(const Card& c1, const Card& c2) const;
};

struct CardReverseComparator {
    bool operator()(const Card& c1, const Card& c2) const;
};

int compareValue(Value& v1, Value& v2);

