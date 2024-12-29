#pragma once
#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "HoleCards.h"
#include "PlayerId.h"
#include "WinningProbabilities.h"

/**
 * @brief Table cards represents all the cards in a game of poker. This includes
 * the deck, board and hole cards.
 *
 */
class TableCards {
  public:
    /**
     * @brief Construct using all the players who are at the table.
     * Notable, does NOT deal cards to the players, or to the board or shuffle
     * the deck.
     *
     * @param players The players at the table
     */
    TableCards(std::vector<PlayerId> players);

    /**
     * @brief Deals cards out to the players until all players have 2 cards.
     *
     * @return void
     */
    void dealPlayerCards();

    /**
     * @brief Deals out cards to the board up to the specified street.
     *
     * @param street
     */
    void dealToStreet(Street street);

    /**
     * @brief Shuffles the deck using the given rng.
     *
     * @param rng Random number generator used to shuffle the deck.
     */
    void shuffleDeck(std::mt19937 &rng);

    /**
     * @brief Returns the probabilities of each player winning the hand (only
     * makes sense given undealt cards). Performs a monte-carlo simulation so
     * this can be a slow operation.
     *
     * @param rng The random number generator used to perform the monte carlo
     * simulation.
     * @return WinningProbabilities
     */
    WinningProbabilities winningProbabilities(std::mt19937 &rng);

    /**
     * @brief Once all the cards have been dealt, this function can be called to
     * get the winners of the hand.
     *
     * @return std::vector<PlayerId> The winner(s) of the hand.
     */
    std::vector<PlayerId> getWinners();

    /**
     * @brief Once all the cards have been dealt, this function can be caleld to
     * get the winners of the hand. Only includes players in eligiblePlayers,
     * which may be a subset of all the players in the hand because players
     * folded out.
     *
     * @param eligiblePlayers
     * @return std::vector<PlayerId>
     */
    std::vector<PlayerId>
    getWinners(const std::vector<PlayerId> &eligiblePlayers);

    /**
     * @brief Only meant for testing. Deals specified cards to the player and
     * removes those cards from the deck
     *
     * @param player
     * @param cards
     */
    void dealToPlayer(PlayerId player, std::vector<Card> cards);

    /**
     * @brief Only meant for testing. Deals specified cards to the board and
     * removes those cards from the deck
     *
     * @param player
     * @param cards
     */
    void dealToBoard(std::vector<Card> cards);

  private:
    /**
     * @brief All the players in the hand. Meant to be set once in the
     * constructor for easy iterating.
     *
     */
    std::vector<PlayerId> players;

    /**
     * @brief The hole cards that each player has.
     *
     */
    std::unordered_map<PlayerId, HoleCards> holeCards;

    /**
     * @brief The cards in the board.
     *
     */
    Board board;

    /**
     * @brief The remaining cards in the deck (full deck minues cards dealt to
     * the players or game)
     *
     */
    Deck deck;
};
