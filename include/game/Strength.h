#pragma once
#include "Card.h"

/**
 * @brief Rank represents the primary types of hands you can make.
 *
 */
enum class Rank {
    STRAIGHT_FLUSH = 9,
    FOUR_OF_A_KIND = 8,
    FULL_HOUSE = 7,
    FLUSH = 6,
    STRAIGHT = 5,
    THREE_OF_A_KIND = 4,
    TWO_PAIR = 3,
    PAIR = 2,
    HIGH_CARD = 1,
    RANK_UNSPECIFIED = 0
};

/**
 * @brief All the ranks in poker.
 *
 */
extern const std::vector<Rank> allRanks;

/**
 * @brief Strength is a comparable object which reflects the strength of any 5
 * card hand, including the rank and any potential kickers.
 *
 */
class Strength {
  private:
    /**
     * @brief Constructs a strength using the given rank and any kickers. Note
     * that unlike the usual definition of kickers which mean any card not part
     * of your primary hand, this class expects you to include the cards in
     * your primary hand in kickers.
     * Kickers is meant to be the cards in your primary hand, sorted by
     * importance, then followed by the traditional kickers, again sorted
     * by importance.
     *
     * For example, a 7 high flush would have only 1 kicker (a 7)
     * This hand : (AA224) would have the kickers {A 2 4}
     *
     * Since this function cannot tell which kickers are which, it will not
     * throw if called incorrectly.
     *
     * @param rank     The primary rank of the hand.
     * @param kickers  The kickers, sorted by importance.
     */
    Strength(Rank rank, std::vector<Value> kickers);

  public:
    /**
     * @brief Constructs an unspecified strength object with undefined contents.
     *
     */
    Strength();

    /**
     * @brief The primary rank.
     *
     */
    Rank rank;

    /**
     * @brief The kickers in the hand, sorted by importance.
     *
     * Kickers is meant to be the cards in your primary hand, sorted by
     * importance, then followed by the traditional kickers, again sorted
     * by importance.
     *
     * For example, a 7 high flush would have only 1 kicker (a 7)
     * This hand : (AA224) would have the kickers {A 2 4}
     *
     * Since this function cannot tell which kickers are which, it will not
     * throw if called incorrectly.
     */
    std::vector<Value> kickers;

    bool operator<(const Strength &other) const;
    bool operator>(const Strength &other) const;
    bool operator==(const Strength &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Strength &strength);

    friend class Hand;
};

std::ostream &operator<<(std::ostream &os, const Strength &strength);

std::ostream &operator<<(std::ostream &os, const Rank &rank);
