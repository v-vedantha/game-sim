#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <random>

Deck::Deck() {
    for (Suit suit : allSuits) {
        for (Value value : allValues) {
            this->cards.push_back(Card(value, suit));
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());
    shuffle(rng);
}

void Deck::shuffle(std::mt19937& rng) {
    std::vector<Card> cardsVec = std::vector<Card>(this->cards.begin(), this->cards.end());
    std::shuffle(cardsVec.begin(), cardsVec.end(), rng);

    this->cards = std::list<Card>(cardsVec.begin(), cardsVec.end());
}

void Deck::deal(std::vector<Card> cardsToDeal) {
    for (const Card& toRemove : cardsToDeal) {
        this->cards.remove_if([&toRemove](Card deckCard){ return deckCard == toRemove; });
    }
}
void Deck::deal(Card cardToDeal) {
    this->cards.remove_if([&cardToDeal](Card deckCard){ return deckCard == cardToDeal; });
}

Card Deck::deal(){
    if (cards.empty()) {
        throw std::invalid_argument("Deck is empty.");
    }

    Card card = cards.front();
    cards.pop_front();

    return card;
}

