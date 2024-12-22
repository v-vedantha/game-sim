#pragma once
#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Potential.h"
#include "Strength.h"

/**
 * @brief Represents the two hidden cards a player has.
 *
 */
class HoleCards {
  public:
    /**
     * @brief Construct with zero cards.
     *
     */
    HoleCards();

    /**
     * @brief Construct with the given cards. Assumes cards has length 2
     *
     * @param cards
     */
    HoleCards(std::vector<Card> cards);

    /**
     * @brief Add the given cards to this hand. Assumes the hand will have <= 2
     * cards after adding the given cards.
     *
     * @param cards
     */
    void addCards(std::vector<Card> cards);

    /**
     * @brief Add the given card to this hand. Assumes the hand will have <= 2
     * cards after adding the given card.
     *
     * @param card
     */
    void addCard(Card card);

    /**
     * @brief Deals cards from the deck to this hand. The resulting hand will
     * have 2 cards.
     *
     * @param deck
     */
    void dealCards(Deck &deck);

    /**
     * @brief Determines the strength of the best 5-card hand using the hole
     * cards and the cards already dealt to the board. Expects the board to have
     * >= 3 cards on it, and this object to have 2 cards in it.
     *
     * @param board
     * @return Strength The strength of the best 5-card hand you can create.
     */
    Strength evaluate(Board &board);

    /**
     * @brief Determines which hands you might potentially make given future
     * undealt cards up to the given street.
     * Expects the board to have <5 cards on it, and the street to be "in the
     * future" relative to cards dealt on the board.
     * Does a monte-carlo simulation internally, so the rng is used to generate
     * randomness.
     *
     * @param board  Must have <5 cards on it
     * @param street The street we will evaluate our potential at. Must be in
     * the future relative to the board. For example, if the board has three
     * cards (on the Flop) then the street must be either the Turn (when the
     * board will have 4 cards), or the River (when the board will have 5 card
     * have 5 cards).
     * @param rng    Random number generator used to run monte carlo simulations
     * of possible runouts.
     * @return Potential Describes the hands you can construct and the odds of
     * constructing them.
     */
    Potential evaluatePotential(Board &board, Street street, std::mt19937 &rng);

  private:
    std::vector<Card> cards;
};
