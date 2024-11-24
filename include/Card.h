#pragma once

enum Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum Value {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

class Card {
    Suit suit;
    Value value;
public:
    Card(Value value, Suit suit);

    bool operator==(const Card& other) const {
        return this->suit == other.suit && this->value == other.value;
    }
};
