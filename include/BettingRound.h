/**
 * @class BettingRound
 * @brief Manages the betting state for a single round within a poker game.
 *
 * The BettingRound class tracks the current bet and handles raise and all-in
 * actions.
 */
class BettingRound {

  public:
    /**
     * @brief Constructs a new BettingRound object.
     *
     * Initializes the current bet to zero.
     */
    BettingRound();

    /**
     * @brief Executes a raise action, setting the current bet to the specified
     * amount.
     *
     * @param amount The amount to which the bet is being raised.
     */
    void raiseTo(int amount);

    /**
     * @brief Executes an all-in action, setting the current bet to the
     * specified all-in amount.
     *
     * @param amount The total amount the player is going all-in with.
     */
    void allIn(int amount);

    /**
     * @brief Retrieves the current bet for the round.
     *
     * @return The current bet amount.
     */
    int currentBet();

  private:
    /**
     * @brief The current bet amount in the betting round.
     */
    int m_currentBet;
};
