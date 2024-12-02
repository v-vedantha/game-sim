#include <map>
#include "Card.h"


Card::Card(Value value, Suit suit) {
    this->value = value;
    this->suit = suit;
}

const std::map<Suit, std::string> suitToString = {
    {Suit::HEARTS, "Hearts"},
    {Suit::DIAMONDS, "Diamonds"},
    {Suit::CLUBS, "Clubs"},
    {Suit::SPADES, "Spades"}
};

const std::map<Value, std::string> valueToString = {
    {Value::TWO, "2"},
    {Value::THREE, "3"},
    {Value::FOUR, "4"},
    {Value::FIVE, "5"},
    {Value::SIX, "6"},
    {Value::SEVEN, "7"},
    {Value::EIGHT, "8"},
    {Value::NINE, "9"},
    {Value::TEN, "10"},
    {Value::JACK, "Jack"},
    {Value::QUEEN, "Queen"},
    {Value::KING, "King"},
    {Value::ACE, "Ace"},
};


std::string Card::toString() const {
    return valueToString.at(this->value) + " of " + suitToString.at(this->suit);
}
