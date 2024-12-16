#include "Board.h"
#include "Hand.h"
#include "Deck.h"
#include "Strength.h"
#include <ostream>

Board::Board() {}
Board::Board(std::vector<Card> cards) : cards(cards) {}

void Board::addCard(Card card) {
    cards.push_back(card);
}

void Board::addCards(std::vector<Card> cards) {
    this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}


int Board::size() {
    return cards.size();
}


std::vector<Card> Board::getCards() {
    return cards;
}

std::map<Street, int> totalCardsAtStreet = {
    {Street::FLOP, 3},
    {Street::TURN, 4},
    {Street::RIVER, 5},
};

void Board::dealToStreet(Deck& deck, Street& street) {
    while (cards.size() < totalCardsAtStreet[street]) {
        addCard(deck.deal());
    }
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    for (int i = 0; i < board.cards.size(); ++i) {
        os << board.cards[i];
    }
    return os;
}
