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

void Deck::shuffle(std::mt19937 &rng) {
    // Shuffle the deck using the given rng seed.

    // std::shuffle accepts vector/array style containers, not lists, so we need
    // to copy the cards into a vector.
    std::vector<Card> cardsVec =
        std::vector<Card>(this->cards.begin(), this->cards.end());
    // Shuffle the cards
    std::shuffle(cardsVec.begin(), cardsVec.end(), rng);

    // And copy them back into the list.
    this->cards = std::list<Card>(cardsVec.begin(), cardsVec.end());
}

void Deck::removeCards(std::vector<Card> cardsToRemove) {
    for (const Card &toRemove : cardsToRemove) {
        // Optionally could validate that the card to remove existed in the
        // deck, which could catch mistakes where people mistakenly remove the
        // same card twice instead of two different cards, but this seems
        // unnecessary for now.
        this->cards.remove_if(
            [&toRemove](Card deckCard) { return deckCard == toRemove; });
    }
}
void Deck::removeCard(Card toRemove) {
    // Optionally could validate that the card to remove existed in the
    // deck, which could catch mistakes where people mistakenly remove the
    // same card twice instead of two different cards, but this seems
    // unnecessary for now.
    this->cards.remove_if(
        [&toRemove](Card deckCard) { return deckCard == toRemove; });
}

Card Deck::deal() {
    // Cannot deal from an empty deck!
    // Not expected in practice. Even with 10 players in holdem poker, you only
    // deal ~25 cards.
    if (cards.empty()) {
        throw std::runtime_error("Deck is empty.");
    }

    Card card = cards.front();

    // Make sure to remove the card from the deck (uses pop_front because its
    // more efficient than removeCard)
    cards.pop_front();

    return card;
}
