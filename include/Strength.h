#pragma once
#include "Card.h"

// Strength represents the strength of a hand. 
// It contains both the rank of the best hand you can create (i.e. flush, quads, etc) and
// the "kickers".
// Unlike the usual definition we include the "main hand" in the kickers
// to let us compare strengths easily. 
// So for example a 3-Aces, 2-Fours hand will have {Rank : Full House; Kickers : {Ace, Four}}


enum class Rank { STRAIGHT_FLUSH=9, FOUR_OF_A_KIND=8, FULL_HOUSE=7, FLUSH=6, STRAIGHT=5, THREE_OF_A_KIND=4, TWO_PAIR=3, PAIR=2, HIGH_CARD=1, RANK_UNSPECIFIED=0 };

extern const std::vector<Rank> allRanks; 

class Strength {
private:
    // Expects kickers to be sorted in descending order of importance
    // I.e. a 3-Aces, 2-Fours hand will have Kickers = {Ace, Four}
    Strength(Rank rank, std::vector<Value> kickers);
public:
    Strength();
    Rank rank;
    // Kickers are in descending order of importance
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
