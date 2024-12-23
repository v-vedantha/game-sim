#pragma once
#include "Card.h"
#include "Deck.h"
#include "Strength.h"

#include <map>
#include <vector>

/**
 * @enum Street
 * @brief Represents the stages of a poker hand based on the number of cards on
 * the board.
 *
 * Streets are the common terms used in poker to represent the progress of a
 * hand:
 * - `PREFLOP`: No cards on the board.
 * - `FLOP`: Three cards on the board.
 * - `TURN`: Four cards on the board.
 * - `RIVER`: Five cards on the board.
 */
enum class Street { STREET_UNSPECIFIED, PREFLOP, FLOP, TURN, RIVER };

/**
 * @brief Returns the nex street. This can throw if the current street is
 * unspecified, or the next street does not exist.
 *
 * @param street The current street.
 * @return The next street in the sequence.
 */
Street nextStreet(Street street);

/**
 * @class Board
 * @brief Represents the community cards on the board during a poker game.
 *
 * The Board class manages the cards dealt to the board, provides functionality
 * to add cards, and handles the transition of the board to a new street.
 */
class Board {
    /**
     * @brief The cards currently on the board.
     */
    std::vector<Card> cards;

  public:
    /**
     * @brief Constructs an empty Board object.
     */
    Board();

    /**
     * @brief Constructs a Board object initialized with a specific set of
     * cards.
     *
     * @param cards A vector of cards to initialize the board with.
     */
    Board(std::vector<Card> cards);

    /**
     * @brief Adds a single card to the board.
     *
     * @param card The card to add.
     */
    void addCard(Card card);

    /**
     * @brief Adds multiple cards to the board.
     *
     * @param cards The cards to add.
     */
    void addCards(std::vector<Card> cards);

    /**
     * @brief Deals cards from the deck to the board for the given street.
     *
     * @param deck The deck from which cards will be dealt.
     * @param street The street to deal to, which determines how many cards are
     * dealt.
     */
    void dealToStreet(Deck &deck, Street &street);

    /**
     * @brief Retrieves the number of cards currently on the board.
     *
     * @return The number of cards on the board.
     */
    int size();

    /**
     * @brief Retrieves the cards currently on the board.
     *
     * @return A vector of cards on the board.
     */
    std::vector<Card> getCards();

    friend std::ostream &operator<<(std::ostream &os, const Board &board);
};

std::ostream &operator<<(std::ostream &os, const Board &board);
