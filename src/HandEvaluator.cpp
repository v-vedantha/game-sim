#include <iostream>
#include <set>
#include "HandEvaluator.h"

#include "Card.h"

typedef struct {
    bool isFlush;
    Value highCard;
} HasFlush;

typedef struct {
    bool isStraight;
    Value highCard;
} HasStraight;

typedef struct {
    bool isQuads;
    Value quadsCard;
    Value kicker;
} HasQuads;

typedef struct {
    bool isFullHouse;
    Value threeOfAKind;
    Value pair;
} HasFullHouse;

typedef struct {
    bool isThreeOfAKind;
    Value threeOfAKind;
    std::array<Value, 2> kickers;
} HasThreeOfAKind;

typedef struct {
    bool isTwoPair;
    // Sorted high to low
    std::array<Value, 2> pairs;
    Value kicker;
} HasTwoPair;

typedef struct {
    bool isPair;
    Value pair;
    std::array<Value, 3> kickers;
} HasPair;

HandEvaluation::HandEvaluation(HandRank rank, std::vector<Value> kickers) {
    // TODO: Ensure the kickers are of the correct size
    this->rank = rank;
    this->kickers = kickers;
}

bool HandEvaluation::operator<(const HandEvaluation& other) const {
    if (this->rank != other.rank) {
        return this->rank < other.rank;
    } else {
        for (int i = 0; i < kickers.size(); i++) {
            // Kicker sizes are the same if the rank is the same
            if (this->kickers[i] != other.kickers[i]) {
                return this->kickers[i] < other.kickers[i];
            }
        }
    }

    return false;
}

bool HandEvaluation::operator>(const HandEvaluation& other) const {
    return !(*this < other);
}

bool HandEvaluation::operator==(const HandEvaluation& other) const {
    if (this->rank != other.rank) {
        return false;
    } else {
        for (int i = 0; i < kickers.size(); i++) {
            if (this->kickers[i] != other.kickers[i]) {
                return false;
            }
        }
    }

    return true;
}

std::vector<Value> sortKickers(const std::vector<Value>& hand) {
    std::vector<Value> sorted_hand = hand;
    std::sort(sorted_hand.begin(), sorted_hand.end(), std::greater<>());
    return sorted_hand;
}     

HasFlush hasFlush(const std::array<Card, 5>& sorted_hand) {
    HasFlush result;
    result.isFlush = true;

    for (int i = 1; i < 5; i++) {
        if (sorted_hand[i].suit != sorted_hand[0].suit) {
            result.isFlush = false;
        }
    }

    result.highCard = sorted_hand[4].value;
    return result;
}


HasStraight hasStraight(const std::array<Card, 5>& sorted_hand) {
    HasStraight result;
    result.isStraight = true;


    // Check for a 5-high straight separately since an Ace is counted as low in only this case
    if (sorted_hand[4].value == Value::ACE &&
            sorted_hand[0].value == Value::TWO &&
            sorted_hand[1].value == Value::THREE &&
            sorted_hand[2].value == Value::FOUR && 
            sorted_hand[3].value == Value::FIVE) {
        result.isStraight = true;
        result.highCard = Value::FIVE;
        return result;
    } 
    for (int i = 1; i < 5; i++) {
        if (static_cast<int>(sorted_hand[i].value) - static_cast<int>(sorted_hand[i-1].value) != 1) {
            result.isStraight = false;
        }
    }
    result.highCard = sorted_hand[4].value;

    return result;
}

HasQuads hasQuads(const std::array<Card, 5>& hand) { 
    HasQuads result;
    result.isQuads = false;
    std::multiset<Value> values;

    for (const Card& card : hand) {
        values.insert(card.value);
    }

    for (const Card& card : hand) {
        if (values.count(card.value) == 4) {
            result.isQuads = true;
            result.quadsCard = card.value;
        }
    }

    for (const Card& card : hand) {
        if (values.count(card.value) == 1) {
            result.kicker = card.value;
        }
    }

    return result;
}



HasFullHouse hasFullHouse(const std::array<Card, 5>& hand) {
    HasFullHouse result;

    std::multiset<Value> values;

    for (const Card& card : hand) {
        values.insert(card.value);
    }

    bool foundTrips = false;
    for (const Card& card : hand) {
        if (values.count(card.value) == 3) {
            foundTrips = true;
            result.threeOfAKind = card.value;
        }
    }

    if (foundTrips) {
        for (const Card& card : hand) {
            if (values.count(card.value) == 2) {
                result.isFullHouse = true;
                result.pair = card.value;
            }
        }
    }

    return result;
}


HasThreeOfAKind hasThreeOfAKind(const std::array<Card, 5>& hand) {
    HasThreeOfAKind result;

    std::multiset<Value> values;

    for (const Card& card : hand) {
        values.insert(card.value);
    }

    for (const Card& card : hand) {
        if (values.count(card.value) == 3) {
            result.isThreeOfAKind = true;
            result.threeOfAKind = card.value;
            break;
        }
    }

    if (result.isThreeOfAKind) {
        std::vector<Value> kickers;
        for (const Card& card : hand) {
            if (card.value != result.threeOfAKind) {
                kickers.push_back(card.value);
            }
        }

        kickers = sortKickers(kickers);
        for (int i = 0; i < result.kickers.size(); i++) {
            result.kickers[i] = kickers[i];
        }
    }

    return result;
}


HasTwoPair hasTwoPair(const std::array<Card, 5>& hand) {
    HasTwoPair result;

    std::multiset<Value> values;

    for (const Card& card : hand) {
        values.insert(card.value);
    }

    bool foundFirstPair = false;
    Value firstPairValue;
    for (const Card& card : hand) {
        if (values.count(card.value) == 2) {
            foundFirstPair = true;
            firstPairValue = card.value;
            break;
        }
    }

    if (!foundFirstPair) {
        result.isTwoPair = false;
        return result;
    }

    bool foundSecondPair = false;
    Value secondPairValue;
    for (const Card& card : hand) {
        if (card.value != firstPairValue && values.count(card.value) == 2) {
            foundSecondPair = true;
            secondPairValue = card.value;
            break;
        }
    }

    if (!foundFirstPair || !foundSecondPair) {
        result.isTwoPair = false;
        return result;
    }

    result.isTwoPair = true;

    result.pairs[0] = firstPairValue > secondPairValue ? firstPairValue : secondPairValue;
    result.pairs[1] = firstPairValue > secondPairValue ? secondPairValue : firstPairValue;

    for (const Card& card : hand) {
        if (card.value != firstPairValue && card.value != secondPairValue) {
            result.kicker = card.value;
        }
    }

    return result;
}



HasPair hasPair(const std::array<Card, 5>& hand) {
    HasPair result;
    result.isPair = false;

    std::multiset<Value> values;

    for (const Card& card : hand) {
        values.insert(card.value);
    }

    for (const Card& card : hand) {
        if (values.count(card.value) == 2) {
            result.isPair = true;
            result.pair = card.value;
            break;
        }
    }


    if (!result.isPair) {
        result.isPair = false;
        return result;
    }

    std::vector<Value> kickers;

    for (const Card& card : hand) {
        if (card.value != result.pair) {
            kickers.push_back(card.value);
        }
    }

    kickers = sortKickers(kickers);

    for (int i = 0; i < result.kickers.size(); i++) {
        result.kickers[i] = kickers[i];
    }

    return result;
}

HandEvaluation evaluateHand(const std::array<Card, 5>& hand) {
    // Sort the hand by value
    std::array<Card, 5> sorted_hand = hand;
    std::sort(sorted_hand.begin(), sorted_hand.end());

    HasFlush flushResult = hasFlush(sorted_hand);
    HasStraight straightResult = hasStraight(sorted_hand);
    if (flushResult.isFlush && straightResult.isStraight) {
        return HandEvaluation(HandRank::STRAIGHT_FLUSH, {straightResult.highCard});
    }

    HasQuads quadsResult = hasQuads(hand);
    if (quadsResult.isQuads) {
        return HandEvaluation(HandRank::FOUR_OF_A_KIND, {quadsResult.quadsCard, quadsResult.kicker});
    }

    HasFullHouse fullHouseResult = hasFullHouse(hand);
    if (fullHouseResult.isFullHouse) {
        return HandEvaluation(HandRank::FULL_HOUSE, {fullHouseResult.threeOfAKind, fullHouseResult.pair});
    }

    if (flushResult.isFlush) {
        return HandEvaluation(HandRank::FLUSH, {flushResult.highCard});
    }

    if (straightResult.isStraight) {
        return HandEvaluation(HandRank::STRAIGHT, {straightResult.highCard});
    }

    HasThreeOfAKind threeOfAKindResult = hasThreeOfAKind(hand);
    if (threeOfAKindResult.isThreeOfAKind) {
        return HandEvaluation(HandRank::THREE_OF_A_KIND, {threeOfAKindResult.threeOfAKind, threeOfAKindResult.kickers[0], threeOfAKindResult.kickers[1]});
    }

    HasTwoPair twoPairResult = hasTwoPair(hand);
    if (twoPairResult.isTwoPair) {
        return HandEvaluation(HandRank::TWO_PAIR, {twoPairResult.pairs[0], twoPairResult.pairs[1], twoPairResult.kicker});
    }

    HasPair pairResult = hasPair(hand);
    if (pairResult.isPair) {
        return HandEvaluation(HandRank::PAIR, {pairResult.pair, pairResult.kickers[0], pairResult.kickers[1], pairResult.kickers[2]});
    }

    

    std::vector<Value> kickers;

    for (const Card& card : hand) {
        kickers.push_back(card.value);
    }
    kickers = sortKickers(kickers);
    return HandEvaluation(HandRank::HIGH_CARD, kickers);
}
