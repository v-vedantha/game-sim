#include "Card.h"
#include "HandRanker.h"
#include "HandEvaluator.h"
#include <iostream>
#include <cassert>
#include <array>
#include <vector>
#include <set>

HandEvaluation bestEvaluation(const std::array<Card, 2>& hiddenCards, const std::array<Card, 5>& board) {
    bool firstHand = true;
    HandEvaluation bestHand = evaluateHand(board);

    std::vector<Card> availableCards;
    for (int i = 0; i < 2; i++) {
        availableCards.push_back(hiddenCards[i]);
    }
    for (int i = 0; i < board.size(); i++) {
        availableCards.push_back(board[i]);
    }

    // Construct every possible 5-card hand and keep track the one with the highest evaluation.
    for (int removeCard1 = 0; removeCard1 < availableCards.size(); removeCard1++) {
        for (int removeCard2 = removeCard1 + 1; removeCard2 < availableCards.size(); removeCard2++) {
            
            std::vector<Card> handVector;
            int idx = 0;
            for (int k = 0; k < 7; ++k)  {
                if (k != removeCard1 && k != removeCard2) {
                    handVector.push_back(availableCards[k]);
                }
            }

            std::array<Card, 5> hand{handVector[0], handVector[1], handVector[2], handVector[3], handVector[4]};

            HandEvaluation currentHand = evaluateHand(hand);

            if (firstHand || currentHand > bestHand) {
                bestHand = currentHand;
                firstHand = false;
            }
        }
    }

    return bestHand;
}

struct HandEvaluationWithIdx {
    HandEvaluation evaluation;
    int idx;

    bool operator<(const HandEvaluationWithIdx& other) const {
        return this->evaluation < other.evaluation;
    }

    bool operator>(const HandEvaluationWithIdx& other) const {
        return !(this->evaluation < other.evaluation);
    }

    bool operator==(const HandEvaluationWithIdx& other) const {
        return this->evaluation == other.evaluation;
    }
};
    

Winner getWinner(const std::vector<std::array<Card, 2>>& hands, const std::array<Card, 5>& board) {
    assert(hands.size() >= 2);

    std::vector<HandEvaluation> evaluations;
    for (int i = 0; i < hands.size(); i++) {
        evaluations.push_back(bestEvaluation(hands[i], board));
    }

    std::vector<HandEvaluationWithIdx> evaluationsWithIdx;
    for (int i = 0; i < evaluations.size(); i++) {
        evaluationsWithIdx.push_back({evaluations[i], i});
    }

    std::sort(evaluationsWithIdx.begin(), evaluationsWithIdx.end(), std::greater<>());

    Winner result;

    // If there is a tie, we don't have a winner
    if (evaluationsWithIdx[0].evaluation == evaluationsWithIdx[1].evaluation) {
        result.hasWinner = false;
        return result;
    }

    result.hasWinner = true;
    result.winnerIdx = evaluationsWithIdx[0].idx;

    return result;
};
