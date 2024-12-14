#include <map>
#include "Card.h"
#include <ostream>
#include <string>


Card::Card(Value value, Suit suit) {
    this->value = value;
    this->suit = suit;
}

Card::Card() {
    this->value = Value::VALUE_UNSPECIFIED;
    this->suit = Suit::SUIT_UNSPECIFIED;
}

const std::map<Suit, std::string> suitToString = {
    {Suit::HEARTS, "Hearts"},
    {Suit::DIAMONDS, "Diamonds"},
    {Suit::CLUBS, "Clubs"},
    {Suit::SPADES, "Spades"}
};

int compareValue(const Value& lhs, const Value& rhs) {
    return static_cast<int>(lhs) - static_cast<int>(rhs);
}

bool CardComparator::operator()(const Card& lhs, const Card& rhs) const {
    return compareValue(lhs.value, rhs.value) < 0;
}

bool CardReverseComparator::operator()(const Card& lhs, const Card& rhs) const {
    return compareValue(lhs.value, rhs.value) > 0;
}

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

std::ostream& operator<<(std::ostream& os, const Value& value) {
    os << valueToString.at(value); 
    return os;
}

std::ostream& operator<<(std::ostream& os, const Suit& suit) {
    os << suitToString.at(suit);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.value;
    os <<  " of ";
    os << card.suit;
    return os;
}


const std::vector<Suit> allSuits = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS, Suit::SPADES};
const std::vector<Value> allValues = {Value::TWO, Value::THREE, Value::FOUR, Value::FIVE, Value::SIX, Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN, Value::JACK, Value::QUEEN, Value::KING, Value::ACE};
