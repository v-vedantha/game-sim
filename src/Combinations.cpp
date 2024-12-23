#include "Combinations.h"
#include <cassert>
#include <iostream>

std::vector<std::vector<Card>> generateCombinations(std::vector<Card> cards,
                                                    uint32_t numToChoose,
                                                    uint32_t startIdx) {
    if (numToChoose == 0) {
        return {};
    }

    if (cards.size() - startIdx == numToChoose) {
        std::vector<Card> remainingCards;
        for (int i = startIdx; i < cards.size(); ++i) {
            remainingCards.push_back(cards[i]);
        }
        return {remainingCards};
    }

    std::vector<std::vector<Card>> withFirstCard =
        generateCombinations(cards, numToChoose - 1, startIdx + 1);
    for (auto it = withFirstCard.begin(); it != withFirstCard.end(); it++) {
        it->push_back(cards[startIdx]);
    }

    std::vector<std::vector<Card>> withoutFirstCard =
        generateCombinations(cards, numToChoose, startIdx + 1);

    withFirstCard.insert(withFirstCard.end(), withoutFirstCard.begin(),
                         withoutFirstCard.end());

    return withFirstCard;
}

std::vector<std::vector<Card>> generateCombinations(std::vector<Card> cards,
                                                    uint32_t numToChoose) {

    return generateCombinations(cards, numToChoose, 0);
}
