#pragma once

#include "Board.h"
#include "PlayerId.h"
#include "PlayersInHand.h"
#include "TableCards.h"
#include <map>
#include <memory>
#include <vector>

/**
 * @class Pot
 * @brief Manages the pot in a poker game, including contributions from players
 * and calculating winnings.
 *
 * The Pot class tracks player contributions for each street, allows adding bets
 * to the pot, and determines the distribution of winnings at the end of a hand.
 */
class Pot {

  public:
    /**
     * @brief Constructs a new Pot object.
     *
     * @param playerIds A vector containing the IDs of all players in the game.
     */
    Pot(std::vector<PlayerId> playerIds);

    /**
     * @brief Starts a new betting round for the specified street.
     *
     * This resets the state of the pot for the new street while retaining
     * cumulative contributions. Must be called at the start of each
     * round.
     *
     * @param street The street for which the betting round is being initiated.
     */
    void startRound(Street street);

    /**
     * @brief Adds a specified amount of chips to the pot for a given player.
     *
     * Updates the player's contribution for the current street.
     *
     * @param playerId The ID of the player making the contribution.
     * @param amount The amount of chips the player is adding to the pot.
     */
    void add(PlayerId playerId, int amount);

    /**
     * @brief Retrieves the total amount of chips a player has contributed to
     * the pot for the given street.
     *
     * @param playerId The ID of the player.
     * @return The total amount the player has put in during the current street.
     */
    int amountBet(Street street, PlayerId playerId);

    /**
     * @brief Calculates and retrieves the distribution of winnings based on the
     * current table cards and players in hand.
     *
     * This method uses the community cards and the active players to determine
     * the share of the pot for each player.
     *
     * @param tableCards The community cards on the table.
     * @param playersInHand The current players who are still in the hand.
     * @return A unique pointer to an unordered map of player IDs to their
     * respective winnings.
     */
    std::unique_ptr<std::unordered_map<PlayerId, int>>
    getWinnings(TableCards &tableCards, PlayersInHand &playersInHand);

  private:
    /**
     * @brief The current street of the game.
     */
    Street street;

    /**
     * @brief Tracks the contributions of each player to the pot for every
     * street.
     *
     */
    std::unordered_map<Street, std::unordered_map<PlayerId, int>> amountsPutIn;
};
