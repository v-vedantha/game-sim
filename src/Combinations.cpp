#include "Combinations.h"
#include <cassert>
#include <iostream>

std::vector<std::vector<Card>>
generateCombinations(const std::vector<Card> &cards, uint32_t numToChoose,
                     uint32_t startIdx) {
    // If we've passed the end of cards, something went wrong
    assert(startIdx < cards.size());
    // If you want to choose zero cards, then there is only one zero-element
    // combination.
    if (numToChoose == 0) {
        return {};
    }

    // If you want to select as many cards as are available to choose from, then
    // there is only one combination (all the remaining cards).
    if (cards.size() - startIdx == numToChoose) {
        std::vector<Card> remainingCards;
        for (int i = startIdx; i < cards.size(); ++i) {
            remainingCards.push_back(cards[i]);
        }
        return {remainingCards};
    }

    // In the general case, you either choose the first card.
    std::vector<std::vector<Card>> withFirstCard =
        generateCombinations(cards, numToChoose - 1, startIdx + 1);
    for (auto it = withFirstCard.begin(); it != withFirstCard.end(); it++) {
        it->push_back(cards[startIdx]);
    }

    // Or you exclude the first card.
    std::vector<std::vector<Card>> withoutFirstCard =
        generateCombinations(cards, numToChoose, startIdx + 1);

    // Combine the two cases
    withFirstCard.insert(withFirstCard.end(), withoutFirstCard.begin(),
                         withoutFirstCard.end());

    return withFirstCard;
}

std::vector<std::vector<Card>>
generateCombinations(const std::vector<Card> &cards, uint32_t numToChoose) {
    assert(cards.size() >= numToChoose);
    return generateCombinations(cards, numToChoose, 0);
}
