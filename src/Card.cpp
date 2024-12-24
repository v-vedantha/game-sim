#include "Card.h"
#include <map>
#include <ostream>
#include <string>

Card::Card(Value value, Suit suit) {
    this->value = value;
    this->suit = suit;
}

Card::Card() {
    // Default constructor should not initialize the value/suit to anything
    // useful
    this->value = Value::VALUE_UNSPECIFIED;
    this->suit = Suit::SUIT_UNSPECIFIED;
}

// Used to pretty print cards
const std::map<Suit, std::string> suitToString = {{Suit::HEARTS, "Hearts"},
                                                  {Suit::DIAMONDS, "Diamonds"},
                                                  {Suit::CLUBS, "Clubs"},
                                                  {Suit::SPADES, "Spades"}};

int compareValue(const Value &lhs, const Value &rhs) {
    // A positive return value means lhs > rhs. 0 means equality, negative means
    // lhs < rhs. Since lhs and rhs are both Value enums, which have int
    // representations, we can just static cast directly to the integer
    // representations
    return static_cast<int>(lhs) - static_cast<int>(rhs);
}

bool CardComparator::operator()(const Card &lhs, const Card &rhs) const {
    // Return true of lhs < rhs
    return compareValue(lhs.value, rhs.value) < 0;
}

bool CardReverseComparator::operator()(const Card &lhs, const Card &rhs) const {
    // Return true of lhs > rhs
    return compareValue(lhs.value, rhs.value) > 0;
}

// Used to to pretty print cards.
const std::map<Value, std::string> valueToString = {
    {Value::TWO, "2"},     {Value::THREE, "3"},     {Value::FOUR, "4"},
    {Value::FIVE, "5"},    {Value::SIX, "6"},       {Value::SEVEN, "7"},
    {Value::EIGHT, "8"},   {Value::NINE, "9"},      {Value::TEN, "10"},
    {Value::JACK, "Jack"}, {Value::QUEEN, "Queen"}, {Value::KING, "King"},
    {Value::ACE, "Ace"},
};

std::ostream &operator<<(std::ostream &os, const Value &value) {
    os << valueToString.at(value);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Suit &suit) {
    os << suitToString.at(suit);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Card &card) {
    os << card.value;
    os << " of ";
    os << card.suit;
    return os;
}

// All the possible suits.
const std::vector<Suit> allSuits = {Suit::HEARTS, Suit::DIAMONDS, Suit::CLUBS,
                                    Suit::SPADES};

// All the possible values.
const std::vector<Value> allValues = {
    Value::TWO,   Value::THREE, Value::FOUR, Value::FIVE, Value::SIX,
    Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN,  Value::JACK,
    Value::QUEEN, Value::KING,  Value::ACE};
