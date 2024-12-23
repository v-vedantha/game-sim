#pragma once

#include "BettingRound.h"
#include "PlayerId.h"
#include "PlayersInHand.h"
#include "Pot.h"
#include "TableCards.h"

#include <map>
#include <memory>
#include <vector>

/**
 * @class IllegalAction
 * @brief Represents an exception thrown when a player attempts an illegal
 * action in the game.
 *
 * Examples of illegal actions include calling a raise without sufficient chips.
 */
class IllegalAction : public std::exception {
    std::string message;

  public:
    /**
     * @brief Constructs an IllegalAction exception with a specific message.
     *
     * @param message A descriptive message explaining the nature of the illegal
     * action.
     */
    IllegalAction(std::string message);

    /**
     * @brief Provides a description of the illegal action.
     *
     * @return A C-style string with the exception message.
     */
    const char *what() const throw();
};

/**
 * @class Bets
 * @brief Manages betting actions, betting rounds, and pots in the game.
 *
 * This class handles player bets, updates the pot, validates actions, and
 * provides information about the betting state for game management.
 */
class Bets {

  public:
    /**
     * @brief Constructs a new Bets object.
     *
     * @param playerIds A list of all players in the game.
     * @param playersInHand A shared pointer to a PlayersInHand object to track
     * player turns.
     */
    Bets(std::vector<PlayerId> playerIds,
         std::shared_ptr<PlayersInHand> playersInHand,
         std::unique_ptr<std::unordered_map<PlayerId, int>> chipStacks);

    /**
     * @brief Starts a new betting round for a given street.
     *
     * This function must be called at the beginning of every new street.
     *
     * @param street The current street for which betting is initiated.
     */
    void startRound(Street street);

    /**
     * @brief Determines the next player to act.
     *
     * If no players can act, the return value is undefined.
     *
     * @return The PlayerId of the next player to act.
     */
    PlayerId nextIdToAct();

    /**
     * @brief Executes a call action for the specified player, updating the pot
     * and game state.
     *
     * @param playerId The ID of the player making the call.
     */
    void call(PlayerId playerId);

    /**
     * @brief Executes a check action for the specified player, updating the
     * game state.
     *
     * @param playerId The ID of the player making the check.
     */
    void check(PlayerId playerId);

    /**
     * @brief Executes a fold action for the specified player, removing them
     * from the hand and updating the game state.
     *
     * @param playerId The ID of the player folding.
     */
    void fold(PlayerId playerId);

    /**
     * @brief Executes a raise action for the specified player, updating the pot
     * and game state with the new bet.
     *
     * @param playerId The ID of the player making the raise.
     * @param amount The amount to raise to.
     */
    void raiseTo(PlayerId playerId, int amount);

    /**
     * @brief Executes an all-in action for the specified player, putting their
     * remaining chips into the pot and updating the game state.
     *
     * @param playerId The ID of the player going all-in.
     */
    void allIn(PlayerId playerId);

    /**
     * @brief Gets the amount required to call the current bet. The amount a
     * player has to contribute to call the bet is {getCallingAmount() -
     * getAmountPutIn()}
     *
     * @return The amount needed to call.
     */
    int getCallingAmount();

    /**
     * @brief Retrieves the amount a specific player has put into the pot on
     * this street.
     *
     * @param playerId The ID of the player.
     * @return The total amount bet by the player.
     */
    int getAmountPutIn(PlayerId playerId);

    /**
     * @brief Checks whether the current betting round is complete.
     *
     * @return True if the betting round is complete, otherwise false.
     */
    bool bettingRoundComplete();

    /**
     * @brief Distribute winnings to their respective players.
     *
     * @param tableCards All the cards in the game. Used to determine who wins
     * the hand
     */
    void distributeWinnings(TableCards &tableCards);

    /**
     * @brief Gets the stack of a particular player.
     *
     * @param playerId The player
     * @return int     Their stack
     */
    int stack(PlayerId playerId);

  private:
    /**
     * @brief A shared pointer to the PlayersInHand object, used to track active
     * players.
     */
    std::shared_ptr<PlayersInHand> playersInHand;

    /**
     * @brief A vector of all player IDs participating in the game.
     */
    std::vector<PlayerId> playerIds;

    /**
     * @brief The current street of the game.
     */
    Street currentStreet;

    /**
     * @brief A map of betting rounds, keyed by street.
     */
    std::unordered_map<Street, std::unique_ptr<BettingRound>> bettingRounds;

    /**
     * @brief The chipStacks each player has remaining (excludes bets placed
     * into the pot)
     *
     */
    std::unique_ptr<std::unordered_map<PlayerId, int>> chipStacks;

    /**
     * @brief The pot that accumulates all bets made by players.
     */
    Pot pot;
};
