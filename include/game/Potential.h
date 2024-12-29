#include "Card.h"
#include "Strength.h"
#include <map>
#include <memory>

/**
 * @brief Describes the hands that are possible from a position. For example, if
 * you have two paired cards, and one card yet to be revealed, there is a chance
 * you make a three of a kind. This class is meant to reflect those chances.
 *
 */
class Potential {
  public:
    /**
     * @brief Returns the chance you have of hitting a particular hand.
     *
     * @param rank The rank of the hand you want to hit
     * @return double The change (0-1.0) that you hit exactly that rank.
     */
    double oddsOfHitting(Rank rank);

    /**
     * @brief Constructs a Potential
     *
     * @param oddsOfHitting A map from rank to the odds of hitting that. Each
     * odds must be [0.0-1.0] and the odds should ideally sum to 1.0
     */
    Potential(std::unique_ptr<std::map<Rank, double>> oddsOfHitting);

  private:
    std::unique_ptr<std::map<Rank, double>> m_oddsOfHitting;
};

/**
 * @brief Helps build a potential object by managing the state needed for a
 * monte carlo simulation of several possible runouts.
 *
 */
class PotentialBuilder {
  public:
    PotentialBuilder();

    /**
     * @brief When running a monte carlo simulation you would typically simulate
     * several runouts. This function is meant to be called with the result of
     * each runout, and updates the PotentialBuilder to reflect the chance you
     * now have of making the given rank.
     *
     * @param rank The rank the particular runout resulted in.
     */
    void addRunout(Rank rank);

    /**
     * @brief Constructs a potential object by dividing each rank's runouts by
     * the total number of runouts.
     *
     * @return Potential
     */
    Potential buildPotential();

  private:
    std::map<Rank, int> numRunoutsWithRank;
};
