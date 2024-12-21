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

void Deck::shuffle(std::mt19937& rng) {
    std::vector<Card> cardsVec = std::vector<Card>(this->cards.begin(), this->cards.end());
    std::shuffle(cardsVec.begin(), cardsVec.end(), rng);

    this->cards = std::list<Card>(cardsVec.begin(), cardsVec.end());
}

void Deck::removeCards(std::vector<Card> cardsToRemove) {
    for (const Card& toRemove : cardsToRemove) {
        this->cards.remove_if([&toRemove](Card deckCard){ return deckCard == toRemove; });
    }
}
void Deck::removeCard(Card toRemove) {
    this->cards.remove_if([&toRemove](Card deckCard){ return deckCard == toRemove; });
}

Card Deck::deal(){
    if (cards.empty()) {
        throw std::invalid_argument("Deck is empty.");
    }

    Card card = cards.front();
    cards.pop_front();

    return card;
}

