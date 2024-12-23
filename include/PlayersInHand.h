#pragma once
#include "PlayerId.h"
#include "TableCards.h"
#include <unordered_set>
#include <vector>

/**
 * @brief This class keeps track of which players are still in the hand as well
 * as whose turn it is.
 *
 */
class PlayersInHand {

  public:
    /**
     * @brief Construct using all the players in the game.
     *
     * @param playerIds All the players in the game
     */
    PlayersInHand(std::vector<PlayerId> playerIds);

    /**
     * @brief Advances the player whose turn it is.
     *
     */
    void advanceCurrentPlayer();

    /**
     * @brief Removes the current player from the hand, meaning they will no
     * longer get any turns and not appear in getPlayersStillInHand. Done when
     * someone folds.
     *
     */
    void removeCurrentPlayerFromHand();

    /**
     * @brief Reopen action for everyone still in the hand. Would normally be
     * done when someone raises.
     *
     */
    void everyoneCanAct();

    /**
     * @brief Removes the player from betting but keeps them in the hand. This
     * is used when a player goes all in so they cannot bet any more chips but
     * still are part of the hand.
     *
     */
    void removeCurrentPlayerFromBetting();

    /**
     * @brief Starts a new betting round, resetting action for everyone.
     *
     */
    void startNewBettingRound();

    /**
     * @brief Returns the next player who must act. If no players can act the
     * return type is undefined.
     *
     * @return PlayerId The next player to act.
     */
    PlayerId nextIdToAct();

    /**
     * @brief Returns the players still in the hand. This is basically everyone
     * except those who folded.
     *
     * @return std::vector<PlayerId>
     */
    std::vector<PlayerId> getPlayersStillInHand();

    /**
     * @brief Returns true if betting is over for the current round
     *
     */
    bool isBettingOver();

  private:
    /**
     * @brief The players who were still in the hand (everyone who has not
     * folded)
     *
     */
    std::vector<PlayerId> playersInHand;

    /**
     * @brief The players who can still bet (playersInHand - players who have
     * gone all in)
     *
     */
    std::unordered_set<PlayerId> playersWhoCanBet;

    /**
     * @brief The player who the action is currently on.
     *
     */
    int currentPlayer;

    /**
     * @brief The last player who can act in the current round.
     *
     */
    int lastPlayer;

    /**
     * @brief Set to true when betting is over for the current round.
     *
     */
    bool m_isBettingOver;
};
