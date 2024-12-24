#include "Board.h"
#include "Deck.h"
#include "Hand.h"
#include "Strength.h"
#include <cassert>
#include <ostream>

Street nextStreet(Street street) {
    switch (street) {
    case Street::STREET_UNSPECIFIED:
        throw std::runtime_error("Not in a street");
    case Street::PREFLOP:
        return Street::FLOP;
    case Street::FLOP:
        return Street::TURN;
    case Street::TURN:
        return Street::RIVER;
    case Street::RIVER:
        throw std::runtime_error("No more streets");
    }
}

Board::Board() {}
Board::Board(std::vector<Card> cards) : cards(cards) {}

void Board::addCard(Card card) {
    // We could check for repeated cards, but because this is only called in the
    // context of tests or monte-carlo simulations (currently), we prefer to do
    // the bare minimum here.
    cards.push_back(card);
}

void Board::addCards(std::vector<Card> cards) {
    // We could check for repeated cards, but because this is only called in the
    // context of tests or monte-carlo simulations (currently), we prefer to do
    // the bare minimum here.
    this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}

int Board::size() { return cards.size(); }

std::vector<Card> Board::getCards() { return cards; }

std::map<Street, int> totalCardsAtStreet = {
    {Street::FLOP, 3},
    {Street::TURN, 4},
    {Street::RIVER, 5},
};

void Board::dealToStreet(Deck &deck, Street street) {
    while (cards.size() < totalCardsAtStreet[street]) {
        // Deck.deal removes the card from the deck, so no need to worry about
        // potential repeated cards.
        cards.push_back(deck.deal());
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (int i = 0; i < board.cards.size(); ++i) {
        os << board.cards[i];
    }
    return os;
}
