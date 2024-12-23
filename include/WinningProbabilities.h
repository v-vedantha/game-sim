#pragma once
#include "PlayerId.h"
#include <map>
#include <vector>

/**
 * @brief This class reflects the probabilities each player has a chance of
 * winning a hand, given undealt cards.
 *
 */
class WinningProbabilities {
  public:
    /**
     * @brief Construct using the odds of each player winning. The odds must be
     * between 0-1 and sum to 1. They should be constructed with all players
     * still in a hand (i.e. not exclude anyone because they dont have a shot of
     * winning because their cards are so bad)
     *
     * @param winningProbabilities The chance each players has of winning the
     * game.
     */
    WinningProbabilities(
        std::unordered_map<PlayerId, double> winningProbabilities);

    /**
     * @brief Gets the probability of the specifid player winning. If the player
     * was not given a winning probability in the constructor, this function
     * will segfault.
     *
     * @param player The player of interest
     * @return double Their chance of winning (0-1.0)
     */
    double getProbabilityOfWinning(PlayerId player);

  private:
    /**
     * @brief The chance of each player winning.
     *
     */
    std::unordered_map<PlayerId, double> winningProbabilities;
};

/**
 * @brief Represents Monte Carlo simulation state to help compute winning
 * probabilities.
 *
 */
class WinningProbabilitiesBuilder {
  public:
    /**
     * @brief Construct using all the players in the game.
     *
     * @param players All the players in the game.
     */
    WinningProbabilitiesBuilder(std::vector<PlayerId> players);

    /**
     * @brief Updates state to reflect the winners in a runout. If N>1 winners
     * are provided each winner is considered to have 1/N additional wins.
     * Meant to be called with every simulated runout.
     *
     * @param winners The winners in the runout
     */
    void addRunoutResult(const std::vector<PlayerId> &winners);

    /**
     * @brief Constructs a winning probabilities object by dividing the number
     * of runouts each player wins in by the total number of runouts simulated.
     *
     * @return WinningProbabilities
     */
    WinningProbabilities winningProbabilities();

  private:
    /**
     * @brief The number of runouts each player wins in. Can be fractional
     * because a player could win half-a-runout for example if two players end
     * up splitting the pot.
     *
     */
    std::unordered_map<PlayerId, double> winningRunouts;
};
