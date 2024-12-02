#pragma once

#include "Card.h"
#include <vector>

enum class HandRank { STRAIGHT_FLUSH=9, FOUR_OF_A_KIND=8, FULL_HOUSE=7, FLUSH=6, STRAIGHT=5, THREE_OF_A_KIND=4, TWO_PAIR=3, PAIR=2, HIGH_CARD=1 };
class HandEvaluation {
public:
    HandRank rank;
    std::vector<Value> kickers;

    HandEvaluation(HandRank rank, std::vector<Value> kickers);

    bool operator<(const HandEvaluation& other) const;
    bool operator>(const HandEvaluation& other) const;
    bool operator==(const HandEvaluation& other) const;
};

HandEvaluation evaluateHand(const std::array<Card, 5>& hand);



