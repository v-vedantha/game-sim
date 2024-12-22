#include "HoleCards.h"
#include "Card.h"
#include "Combinations.h"
#include "Deck.h"
#include "Hand.h"
#include <iostream>
#include <vector>

HoleCards::HoleCards() {}

HoleCards::HoleCards(std::vector<Card> cards) { this->cards = cards; }

void HoleCards::addCards(std::vector<Card> cards) {
    for (const Card &card : cards) {
        this->cards.push_back(card);
    }
}

void HoleCards::addCard(Card card) { this->cards.push_back(card); }

void HoleCards::dealCards(Deck &deck) {
    while (this->cards.size() < 2) {
        Card card = deck.deal();
        this->cards.push_back(card);
    }
}

Strength HoleCards::evaluate(Board &board) {
    std::vector<Card> allCards;
    for (const Card &card : this->cards) {
        allCards.push_back(card);
    }
    for (const Card &card : board.getCards()) {
        allCards.push_back(card);
    }

    std::vector<std::vector<Card>> combinations =
        generateCombinations(allCards, 5);

    bool isFirst = true;
    Strength strongest;
    for (const std::vector<Card> &combination : combinations) {
        Hand hand(combination);
        Strength strength = hand.evaluate();
        if (isFirst || strength > strongest) {
            strongest = strength;
        }
        isFirst = false;
    }

    return strongest;
}

Potential HoleCards::evaluatePotential(Board &board, Street street,
                                       std::mt19937 &rng) {

    Deck deck;
    deck.removeCards(cards);
    deck.removeCards(board.getCards());

    PotentialBuilder potentialBuilder;

    for (int i = 0; i < 10000; i++) {
        Deck deckCopy = deck;
        Board boardCopy = board;

        deckCopy.shuffle(rng);
        boardCopy.dealToStreet(deckCopy, street);

        Strength strengthOfRunout = evaluate(boardCopy);
        potentialBuilder.addRunout(strengthOfRunout.rank);
    }
    return potentialBuilder.buildPotential();
}
