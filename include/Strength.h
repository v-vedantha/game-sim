#pragma once
#include "Card.h"

enum class Rank { STRAIGHT_FLUSH=9, FOUR_OF_A_KIND=8, FULL_HOUSE=7, FLUSH=6, STRAIGHT=5, THREE_OF_A_KIND=4, TWO_PAIR=3, PAIR=2, HIGH_CARD=1, RANK_UNSPECIFIED=0 };

extern const std::vector<Rank> allRanks; // = {Value::TWO, Value::THREE, Value::FOUR, Value::FIVE, Value::SIX, Value::SEVEN, Value::EIGHT, Value::NINE, Value::TEN, Value::JACK, Value::QUEEN, Value::KING, Value::ACE};

class Strength {
private:
    Strength(Rank rank, std::vector<Value> kickers);
public:
    Strength();
    Rank rank;
    // Sorted in descending order of importance
    // This will include the cards in the "main hand"
    // i.e. an ace high straight will have kickers = {ACE};
    std::vector<Value> kickers;
    bool operator<(const Strength& other) const;
    bool operator>(const Strength& other) const;
    bool operator==(const Strength& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Strength& strength);

    friend class Hand;
};

std::ostream& operator<<(std::ostream& os, const Strength& strength);

std::ostream& operator<<(std::ostream& os, const Rank& rank);
