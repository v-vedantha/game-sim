#pragma once
#include "Card.h"
#include <vector>

/**
 * @brief Generates all possible numToChoose size combinations of the input
 * cards. Can be called to, for example, generate all possible 5-card
 * combinations of a 7 card board+hand when trying to figure out what the
 * strongest 5-card hand is.
 *
 * @param cards
 * @param numToChoose
 * @return std::vector<std::vector<Card>> Vector of length cards.size() Choose
 * numToChoose
 */
std::vector<std::vector<Card>>
generateCombinations(const std::vector<Card> &cards, uint32_t numToChoose);
