#include "Strength.h"
#include <cassert>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

// Used for pretty printing
std::unordered_map<Rank, std::string> rankToString = {
    {Rank::HIGH_CARD, "HIGH_CARD"},
    {Rank::PAIR, "PAIR"},
    {Rank::TWO_PAIR, "TWO_PAIR"},
    {Rank::THREE_OF_A_KIND, "THREE_OF_A_KIND"},
    {Rank::STRAIGHT, "STRAIGHT"},
    {Rank::FLUSH, "FLUSH"},
    {Rank::FULL_HOUSE, "FULL_HOUSE"},
    {Rank::FOUR_OF_A_KIND, "FOUR_OF_A_KIND"},
    {Rank::STRAIGHT_FLUSH, "STRAIGHT_FLUSH"},
    {Rank::RANK_UNSPECIFIED, "RANK_UNSPECIFIED"}};

// Depending on the rank, we expect a different number of kickers needed to
// compare two hands of the same rank. For example, two straights are only
// differentiated by the highest card in that straight, but a full-house is
// defined by both cards in the full house.
std::unordered_map<Rank, int> expectedKickers = {
    {Rank::HIGH_CARD, 5},      {Rank::PAIR, 4},
    {Rank::TWO_PAIR, 3},       {Rank::THREE_OF_A_KIND, 3},
    {Rank::STRAIGHT, 1},       {Rank::FLUSH, 5},
    {Rank::FULL_HOUSE, 2},     {Rank::FOUR_OF_A_KIND, 2},
    {Rank::STRAIGHT_FLUSH, 1}, {Rank::RANK_UNSPECIFIED, 0}};

std::ostream &operator<<(std::ostream &os, const Rank &rank) {
    os << rankToString.at(rank);
    return os;
}

Strength::Strength(Rank rank, std::vector<Value> kickers) {
    assert(kickers.size() == expectedKickers[rank]);
    this->rank = rank;
    this->kickers = kickers;
}
Strength::Strength() { this->rank = Rank::RANK_UNSPECIFIED; }

bool Strength::operator<(const Strength &other) const {
    if (this->rank != other.rank) {
        return this->rank < other.rank;
    } else {
        // Since the ranks match, both this and other have the same number of
        // kickers.
        for (int i = 0; i < kickers.size(); i++) {
            if (this->kickers[i] != other.kickers[i]) {
                return this->kickers[i] < other.kickers[i];
            }
        }
    }

    return false;
}

bool Strength::operator>(const Strength &other) const {
    if (this->rank != other.rank) {
        return this->rank > other.rank;
    } else {
        // Since the ranks match, both this and other have the same number of
        // kickers.
        for (int i = 0; i < kickers.size(); i++) {
            if (this->kickers[i] != other.kickers[i]) {
                return this->kickers[i] > other.kickers[i];
            }
        }
    }
    return false;
}

bool Strength::operator==(const Strength &other) const {
    if (this->rank != other.rank) {
        return false;
    } else {
        // Since the ranks match, both this and other have the same number of
        // kickers.
        for (int i = 0; i < kickers.size(); i++) {
            if (this->kickers[i] != other.kickers[i]) {
                return false;
            }
        }
    }

    return true;
}

std::ostream &operator<<(std::ostream &os, const Strength &strength) {
    os << strength.rank;
    for (int i = 0; i < strength.kickers.size(); i++) {
        os << " ";
        os << strength.kickers[i];
    }
    return os;
}

const std::vector<Rank> allRanks = {
    Rank::STRAIGHT_FLUSH, Rank::FOUR_OF_A_KIND, Rank::FULL_HOUSE,
    Rank::FLUSH,          Rank::STRAIGHT,       Rank::THREE_OF_A_KIND,
    Rank::TWO_PAIR,       Rank::PAIR,           Rank::HIGH_CARD};
