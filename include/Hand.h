#pragma once
#include "Card.h"
#include "Strength.h"
#include <vector>
#include <set>


struct HasFlush {
    bool isFlush;
    std::array<Value, 5> kickers;
};

struct HasStraight {
    bool isStraight;
    Value highCard;
};

struct HasQuads {
    bool isQuads;
    Value quadsCard;
    Value kicker;
};

struct HasFullHouse {
    bool isFullHouse;
    Value threeOfAKind;
    Value pair;
};

 struct  HasThreeOfAKind{
    bool isThreeOfAKind;
    Value threeOfAKind;
    std::array<Value, 2> kickers;
} ;

 struct HasTwoPair{
    bool isTwoPair;
    // Sorted high to low
    std::array<Value, 2> pairs;
    Value kicker;
} ;

 struct  HasPair{
    bool isPair;
    Value pair;
    std::array<Value, 3> kickers;
} ;

class Hand {
private:
    // Always stored in descending order
    std::array<Card, 5> cards;   
    std::multiset<Value> values;
    HasFlush hasFlush();
    HasStraight hasStraight();
    HasQuads hasQuads();
    HasFullHouse hasFullHouse();
    HasThreeOfAKind hasThreeOfAKind();
    HasTwoPair hasTwoPair();
    HasPair hasPair();

    void setCards(std::array<Card, 5> cards);

public:
    Hand(std::array<Card, 5> cards);
    Hand(std::vector<Card> cards);

    Strength evaluate();
};
