#include "Hand.h"
#include <cassert>
#include <iostream>

void Hand::setCards(std::array<Card, 5> cards) {
    // We rely on the cards being sorted to simplify checking for straights
    this->cards = cards;
    std::sort(this->cards.begin(), this->cards.end(), CardReverseComparator());

    // this->values is used to count the number of each card, which is used to
    // check for full houses for example
    this->values.clear();
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

    // A flush is defined by all cards being the same suit
    for (int i = 1; i < 5; i++) {
        if (cards[i].suit != cards[0].suit) {
            result.isFlush = false;
        }
    }

    if (result.isFlush) {
        // All the cards in a flush are considered kickers since they all define
        // the strength of the hand.
        // Since the cards are already sorted, the kickers are just the cards in
        // order.
        for (int i = 0; i < result.kickers.size(); i++) {
            result.kickers[i] = cards[i].value;
        }
    }
    return result;
}

HasStraight Hand::hasStraight() {
    HasStraight result;
    result.isStraight = true;
    // A straight means you have five consecutively valued cards.
    // This is the only place where an Ace can have value 1 or 14.

    // The only straight formed with a low Ace is A, 2, 3, 4, 5.
    // Check for this case specially.
    if (cards[0].value == Value::ACE && cards[4].value == Value::TWO &&
        cards[3].value == Value::THREE && cards[2].value == Value::FOUR &&
        cards[1].value == Value::FIVE) {
        result.isStraight = true;
        result.highCard = Value::FIVE;
        return result;
    }

    // In the usual case we can just compare adjacent cards since the cards are
    // sorted to check if they are consecutive.
    for (int i = 0; i < 4; i++) {
        if (static_cast<int>(cards[i].value) -
                static_cast<int>(cards[i + 1].value) !=
            1) {
            result.isStraight = false;
        }
    }

    // The high card of a straight is just the first card since cards is sorted
    result.highCard = cards[0].value;

    return result;
}

HasQuads Hand::hasQuads() {
    // Quads means you have four of a kind, and then one other card. For example
    // 2, 2, 2, 2, A.
    HasQuads result;
    result.isQuads = false;

    for (const Card &card : cards) {
        if (values.count(card.value) == 4) {
            result.isQuads = true;
            result.quadsCard = card.value;
        }
    }

    for (const Card &card : cards) {
        // The kicker is the only card which is not part of the quads.
        if (values.count(card.value) == 1) {
            result.kicker = card.value;
        }
    }

    return result;
}

HasFullHouse Hand::hasFullHouse() {
    // A full house means you have a three of a kind and a two of a kind.
    HasFullHouse result;
    result.isFullHouse = false;

    // Search for the three of a kind
    bool foundTrips = false;
    for (const Card &card : cards) {
        if (values.count(card.value) == 3) {
            foundTrips = true;
            result.threeOfAKind = card.value;
        }
    }

    if (foundTrips) {
        // If we found it search for the two of a kind
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
    // Example of a three of a kind: A,A,A,K,Q
    HasThreeOfAKind result;
    result.isThreeOfAKind = false;

    for (const Card &card : cards) {
        if (values.count(card.value) == 3) {
            result.isThreeOfAKind = true;
            result.threeOfAKind = card.value;
            break;
        }
    }

    if (result.isThreeOfAKind) {
        // The kickers in the three of a kind are both the non-tripled cards so
        // in the example its the K,Q
        std::vector<Value> kickers;
        for (const Card &card : cards) {
            if (card.value != result.threeOfAKind) {
                kickers.push_back(card.value);
            }
        }

        // Make sure to sort the kickers since Strength relies on this.
        std::sort(kickers.begin(), kickers.end(), std::greater<>());
        for (int i = 0; i < kickers.size(); i++) {
            result.kickers[i] = kickers[i];
        }
    }

    return result;
}

HasTwoPair Hand::hasTwoPair() {
    // Example of a two pair: AA, QQ, K
    HasTwoPair result;

    bool foundFirstPair = false;

    // In the example should be either A or Q
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

    // In the example this should be the other one of A or Q
    Value secondPairValue;
    for (const Card &card : cards) {
        if (card.value != firstPairValue && values.count(card.value) == 2) {
            foundSecondPair = true;
            secondPairValue = card.value;
            break;
        }
    }

    if (foundFirstPair && foundSecondPair) {
        result.isTwoPair = true;

        result.pairs[0] =
            firstPairValue > secondPairValue ? firstPairValue : secondPairValue;
        result.pairs[1] =
            firstPairValue > secondPairValue ? secondPairValue : firstPairValue;

        for (const Card &card : cards) {
            // There is only one kicker (in the example it is the K)
            if (card.value != firstPairValue && card.value != secondPairValue) {
                result.kicker = card.value;
            }
        }
    } else {
        result.isTwoPair = false;
    }

    return result;
}

HasPair Hand::hasPair() {
    // An example of a paired hand : A, A, Q, K, J
    HasPair result;
    result.isPair = false;

    for (const Card &card : cards) {
        if (values.count(card.value) == 2) {
            result.isPair = true;
            // In the example this is the A.
            result.pair = card.value;
            break;
        }
    }

    if (!result.isPair) {
        return result;
    }

    std::vector<Value> kickers;

    // The kickers are Q, K, J in the example
    for (const Card &card : cards) {
        if (card.value != result.pair) {
            kickers.push_back(card.value);
        }
    }

    // Remember to sort the kickers since Strength relies on this
    std::sort(kickers.begin(), kickers.end(), std::greater<>());

    for (int i = 0; i < result.kickers.size(); i++) {
        result.kickers[i] = kickers[i];
    }

    return result;
}

Strength Hand::evaluate() {
    // See https://www.pokernews.com/poker-hands.htm for how to rank poker
    // hands.
    HasFlush flushResult = hasFlush();
    HasStraight straightResult = hasStraight();
    if (flushResult.isFlush && straightResult.isStraight) {
        return Strength(Rank::STRAIGHT_FLUSH, {straightResult.highCard});
    }

    HasQuads quadsResult = hasQuads();
    if (quadsResult.isQuads) {
        return Strength(Rank::FOUR_OF_A_KIND,
                        // The first point of comparison between two quads hands
                        // is the man quads card, followed by the kicker, so the
                        // kickers are arranged accordingly.
                        {quadsResult.quadsCard, quadsResult.kicker});
    }

    HasFullHouse fullHouseResult = hasFullHouse();
    if (fullHouseResult.isFullHouse) {
        return Strength(Rank::FULL_HOUSE,
                        // The first point of comparison between two full houses
                        // is the triple, then the pair, so the kickers are
                        // arranged accordingly.
                        {fullHouseResult.threeOfAKind, fullHouseResult.pair});
    }

    if (flushResult.isFlush) {
        // Flushes are compared by all the cards in the hand.
        std::vector<Value> kickers(flushResult.kickers.begin(),
                                   flushResult.kickers.end());

        return Strength(Rank::FLUSH, {kickers});
    }

    if (straightResult.isStraight) {
        // Straights are defined by a single card (i.e. A-high straight), so
        // they are only compared amongs each other by that one card.
        return Strength(Rank::STRAIGHT, {straightResult.highCard});
    }

    HasThreeOfAKind threeOfAKindResult = hasThreeOfAKind();
    if (threeOfAKindResult.isThreeOfAKind) {
        // Three of a kinds are compared by the kind that is tripled up,
        // followed by the two other cards.
        return Strength(Rank::THREE_OF_A_KIND, {threeOfAKindResult.threeOfAKind,
                                                threeOfAKindResult.kickers[0],
                                                threeOfAKindResult.kickers[1]});
    }

    HasTwoPair twoPairResult = hasTwoPair();
    if (twoPairResult.isTwoPair) {
        // Two-pairs are compared by the pairs (higher pair first), followed by
        // the 5-th card.
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

    // When comparing between two high cards, all the five cards are used, so
    // they all end up as kickers.
    std::vector<Value> kickers;

    for (const Card &card : cards) {
        kickers.push_back(card.value);
    }

    // Cards are already sorted, so no need to sort the kickers again.
    return Strength(Rank::HIGH_CARD, kickers);
}
