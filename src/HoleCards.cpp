#include "HoleCards.h"
#include "Card.h"
#include "Deck.h"
#include "Combinations.h"
#include "Hand.h"
#include <vector>
#include <iostream>

HoleCards::HoleCards() {
    
}

HoleCards::HoleCards(std::vector<Card> cards) {
    this->cards = cards;
}

void HoleCards::deal(std::vector<Card> cards) {
    for (const Card& card : cards) {
        this->cards.push_back(card);
    }
}

void HoleCards::deal(Card card) {
    this->cards.push_back(card);
}

Strength HoleCards::evaluate(Board& board) {
    std::vector<Card> allCards;
    for (const Card& card : this->cards) {
        allCards.push_back(card);
    }
    for (const Card& card : board.getCards()) {
        allCards.push_back(card);
    }

    std::vector<std::vector<Card>> combinations = generateCombinations(allCards, 5);

    bool isFirst = true;
    Strength strongest;
    for (const std::vector<Card>& combination : combinations) {
        Hand hand(combination);
        Strength strength = hand.evaluate();
        if (isFirst || strength > strongest) {
            strongest = strength;
        }
        isFirst = false;
    }

    return strongest;
}

Potential HoleCards::evaluatePotential(Board& board, Street& street, int randomSeed) {
    std::mt19937 g(randomSeed);

    Deck deck;
    for (Card card : cards) {
        deck.deal(card);
    }
    for (Card card : board.getCards()) {
        deck.deal(card);
    }

    PotentialBuilder potentialBuilder;

    for (int i = 0; i < 10000; i++) {
        Deck deckCopy = deck;
        Board boardCopy = board;

        deckCopy.shuffle(g);
        boardCopy.dealToStreet(deckCopy, street);

        Strength strengthOfRunout = evaluate(boardCopy);
        potentialBuilder.addRunout(strengthOfRunout.rank);
    }
    return potentialBuilder.buildPotential();
}
