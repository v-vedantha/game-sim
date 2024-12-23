#pragma once
#include "Bets.h"
#include "PlayerId.h"
#include "TableCards.h"
#include <map>
#include <memory>

class Player;

/**
 * @class Game
 * @brief Oversees a full game of poker, the cards, betting, and chipstacks.
 *
 */
class Game {

  public:
    /**
     * @brief Finishes a game, distributing winnings to respecitve players.
     *
     */
    void finish();

    /**
     * @brief Deals out the the next street of cards to the board. Requires that
     * betting for the current street is complete.
     *
     */
    void dealToNextStreet();

    /**
     * @brief Determines the next player to act. If no players can act (i.e. the
     * betting round is complete) then will return undefined value.
     *
     * @return PlayerId The id of the next player to act
     */
    PlayerId nextIdToAct();

    /**
     * @brief Executes a check by the given player.
     *
     * @throw Can throw if the given player is not allowed to check because a
     * previous player bet.
     * @param playerId The player who is checking
     */
    void check(PlayerId playerId);

    /**
     * @brief Executes a call by the given player.
     *
     * @throw Can throw if the given player has insufficient funds or not their
     * turn
     * @param playerId The player who is calling
     */
    void call(PlayerId playerId);

    /**
     * @brief Executes a raise for the given player.
     *
     * @throw Can throw if the given player has insufficient funds, or not their
     * turn.
     * @param playerId The player who is raising
     * @param amount The total amount the player has put into the pot this
     * street after the raise. Not the amount the player is "raising by"
     */
    void raiseTo(PlayerId playerId, int amount);

    /**
     * @brief Executes an allIn for the given player. They will not need to act
     * in future rounds as they are already all in.
     *
     * @param playerId The player who is going allIn.
     */
    void allIn(PlayerId playerId);

    /**
     * @brief Gets the stack of a particular player.
     *
     * @param playerId The player
     * @return int     Their stack
     */
    int stack(PlayerId playerId);

    /**
     * @brief Construct a game given some players, their chipStacks, and a
     * random number generator.
     *
     * @param playerIds The players in the game. Betting order proceeds from the
     * first player in this vector onwards.
     * @param chips     The initial chip stacks.
     * @param rng       Random number generater. Used to shuffle the deck etc.
     */
    Game(std::vector<PlayerId> playerIds,
         std::unique_ptr<std::unordered_map<PlayerId, int>> chips,
         std::mt19937 &rng);

  private:
    std::vector<std::weak_ptr<PlayerId>> players;

    TableCards tableCards;

    // Game owns playersInHand. Bets stores an additional reference
    std::shared_ptr<PlayersInHand> playersInHand;

    Bets bets;

    Street street;
};
