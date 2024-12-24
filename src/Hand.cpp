#include "Hand.h"
#include <cassert>
#include <iostream>

void Hand::setCards(std::array<Card, 5> cards) {
    this->cards = cards;
    std::sort(this->cards.begin(), this->cards.end(), CardReverseComparator());

    for (const Card &card : this->cards) {
        this->values.insert(card.value);
    }
}

Hand::Hand(std::array<Card, 5> cards) { setCards(cards); }

Hand::Hand(std::vector<Card> cards) {
    std::array<Card, 5> cardsArray;
    for (int i = 0; i < 5; i++) {
        cardsArray[i] = cards[i];
    }
    setCards(cardsArray);
}

HasFlush Hand::hasFlush() {
    HasFlush result;
    result.isFlush = true;

    for (int i = 1; i < 5; i++) {
        if (cards[i].suit != cards[0].suit) {
            result.isFlush = false;
        }
    }

    for (int i = 0; i < result.kickers.size(); i++) {
        result.kickers[i] = cards[i].value;
    }
    return result;
}

HasStraight Hand::hasStraight() {
    HasStraight result;
    result.isStraight = true;
    // Check for a 5-high straight separately since an Ace is counted as low in
    // this case
    if (cards[0].value == Value::ACE && cards[4].value == Value::TWO &&
        cards[3].value == Value::THREE && cards[2].value == Value::FOUR &&
        cards[1].value == Value::FIVE) {
        result.isStraight = true;
        result.highCard = Value::FIVE;
        return result;
    }
    for (int i = 0; i < 4; i++) {
        if (static_cast<int>(cards[i].value) -
                static_cast<int>(cards[i + 1].value) !=
            1) {
            result.isStraight = false;
        }
    }
    result.highCard = cards[0].value;

    return result;
}

HasQuads Hand::hasQuads() {
    HasQuads result;
    result.isQuads = false;

    for (const Card &card : cards) {
        if (values.count(card.value) == 4) {
            result.isQuads = true;
            result.quadsCard = card.value;
        }
    }

    for (const Card &card : cards) {
        if (values.count(card.value) == 1) {
            result.kicker = card.value;
        }
    }

    return result;
}

HasFullHouse Hand::hasFullHouse() {
    HasFullHouse result;

    bool foundTrips = false;
    for (const Card &card : cards) {
        if (values.count(card.value) == 3) {
            foundTrips = true;
            result.threeOfAKind = card.value;
        }
    }

    if (foundTrips) {
        for (const Card &card : cards) {
            if (values.count(card.value) == 2) {
                result.isFullHouse = true;
                result.pair = card.value;
            }
        }
    }

    return result;
}

HasThreeOfAKind Hand::hasThreeOfAKind() {
    HasThreeOfAKind result;
    result.isThreeOfAKind = false;

    std::multiset<Value> values;

    for (const Card &card : cards) {
        values.insert(card.value);
    }

    for (const Card &card : cards) {
        if (values.count(card.value) == 3) {
            result.isThreeOfAKind = true;
            result.threeOfAKind = card.value;
            break;
        }
    }

    if (result.isThreeOfAKind) {
        std::vector<Value> kickers;
        for (const Card &card : cards) {
            if (card.value != result.threeOfAKind) {
                kickers.push_back(card.value);
            }
        }

        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        for (int i = 0; i < kickers.size(); i++) {
            result.kickers[i] = kickers[i];
        }
    }

    return result;
}

HasTwoPair Hand::hasTwoPair() {
    HasTwoPair result;

    std::multiset<Value> values;

    for (const Card &card : cards) {
        values.insert(card.value);
    }

    bool foundFirstPair = false;
    Value firstPairValue;
    for (const Card &card : cards) {
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
    for (const Card &card : cards) {
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

    result.pairs[0] =
        firstPairValue > secondPairValue ? firstPairValue : secondPairValue;
    result.pairs[1] =
        firstPairValue > secondPairValue ? secondPairValue : firstPairValue;

    for (const Card &card : cards) {
        if (card.value != firstPairValue && card.value != secondPairValue) {
            result.kicker = card.value;
        }
    }

    return result;
}

HasPair Hand::hasPair() {
    HasPair result;
    result.isPair = false;

    for (const Card &card : cards) {
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

    for (const Card &card : cards) {
        if (card.value != result.pair) {
            kickers.push_back(card.value);
        }
    }

    std::sort(kickers.begin(), kickers.end(), std::greater<>());

    for (int i = 0; i < result.kickers.size(); i++) {
        result.kickers[i] = kickers[i];
    }

    return result;
}

Strength Hand::evaluate() {
    HasFlush flushResult = hasFlush();
    HasStraight straightResult = hasStraight();
    if (flushResult.isFlush && straightResult.isStraight) {
        return Strength(Rank::STRAIGHT_FLUSH, {straightResult.highCard});
    }

    HasQuads quadsResult = hasQuads();
    if (quadsResult.isQuads) {
        return Strength(Rank::FOUR_OF_A_KIND,
                        {quadsResult.quadsCard, quadsResult.kicker});
    }

    HasFullHouse fullHouseResult = hasFullHouse();
    if (fullHouseResult.isFullHouse) {
        return Strength(Rank::FULL_HOUSE,
                        {fullHouseResult.threeOfAKind, fullHouseResult.pair});
    }

    if (flushResult.isFlush) {
        std::vector<Value> kickers;

        for (const Card &card : cards) {
            kickers.push_back(card.value);
        }
        return Strength(Rank::FLUSH, {kickers});
    }

    if (straightResult.isStraight) {
        return Strength(Rank::STRAIGHT, {straightResult.highCard});
    }

    HasThreeOfAKind threeOfAKindResult = hasThreeOfAKind();
    if (threeOfAKindResult.isThreeOfAKind) {
        return Strength(Rank::THREE_OF_A_KIND, {threeOfAKindResult.threeOfAKind,
                                                threeOfAKindResult.kickers[0],
                                                threeOfAKindResult.kickers[1]});
    }

    HasTwoPair twoPairResult = hasTwoPair();
    if (twoPairResult.isTwoPair) {
        return Strength(Rank::TWO_PAIR,
                        {twoPairResult.pairs[0], twoPairResult.pairs[1],
                         twoPairResult.kicker});
    }

    HasPair pairResult = hasPair();
    if (pairResult.isPair) {
        return Strength(Rank::PAIR,
                        {pairResult.pair, pairResult.kickers[0],
                         pairResult.kickers[1], pairResult.kickers[2]});
    }

    // In a high card everything is a kicker
    std::vector<Value> kickers;

    for (const Card &card : cards) {
        kickers.push_back(card.value);
    }
    std::sort(kickers.begin(), kickers.end(), std::greater<>());
    return Strength(Rank::HIGH_CARD, kickers);
}
