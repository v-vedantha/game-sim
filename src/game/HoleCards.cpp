#include "HoleCards.h"
#include "Card.h"
#include "Combinations.h"
#include "Deck.h"
#include "Hand.h"
#include <cassert>
#include <iostream>
#include <vector>

HoleCards::HoleCards() {}

HoleCards::HoleCards(std::vector<Card> cards) { this->cards = cards; }

void HoleCards::addCards(std::vector<Card> cards) {
    for (const Card &card : cards) {
        // Could check for repeated cards here if wanted.
        this->cards.push_back(card);
    }
}

void HoleCards::addCard(Card card) { this->cards.push_back(card); }

void HoleCards::dealCards(Deck &deck) {
    while (this->cards.size() < 2) {
        // Deck.deal removes the cards from the deck, so no need to check for
        // repeated cards.
        Card card = deck.deal();
        this->cards.push_back(card);
    }
}

Strength HoleCards::evaluate(Board &board) {

    // Step 1: To evaluate the best 5 card hand constructed with the hole cards
    // and the board, we first generate all possible 5 card hands from these
    // two.

    // Combine all the cards together into one vector.
    std::vector<Card> allCards;
    for (const Card &card : this->cards) {
        allCards.push_back(card);
    }
    for (const Card &card : board.getCards()) {
        allCards.push_back(card);
    }
    // Generate all 5 card combinations.
    std::vector<std::vector<Card>> combinations =
        generateCombinations(allCards, 5);

    // Ensure there is atleast one-combination of 5 card hands.
    assert(combinations.size() > 0);

    // Step 2: Evaluate the strength of each 5 card hand and return the
    // strongest one.
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

    // Since there is atleast one combination of 5-card hands, strongest is
    // guarunteed to have been set within the preceeding for loop.
    return strongest;
}

Potential HoleCards::evaluatePotential(Board &board, Street street,
                                       std::mt19937 &rng) {

    // Our strategy for evaluating the potential of a hand is to run out the
    // board to the given street several times, and figure out which hands we
    // were able to construct.

    // All we have access to are the board cards and the cards in our hand (not
    // the cards in other players hands), so we can build a deck containing all
    // the cards we can expect to show up.
    Deck deck;
    deck.removeCards(cards);
    deck.removeCards(board.getCards());

    PotentialBuilder potentialBuilder;

    // Then we simulate several runouts
    for (int i = 0; i < 10000; i++) {
        Deck deckCopy = deck;
        Board boardCopy = board;

        // Make sure to shuffle the deck so each runout is different
        deckCopy.shuffle(rng);

        // Deal the board out to the given street
        boardCopy.dealToStreet(deckCopy, street);

        // And log the strength of the hand this runout gave us.
        Strength strengthOfRunout = evaluate(boardCopy);
        potentialBuilder.addRunout(strengthOfRunout.rank);
    }
    return potentialBuilder.buildPotential();
}
