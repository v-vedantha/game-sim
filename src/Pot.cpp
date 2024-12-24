#include "Pot.h"
#include <iostream>

Pot::Pot(std::vector<PlayerId> playerIds) { this->playerIds = playerIds; }

void Pot::startRound(Street street) {
    this->street = street;
    amountsPutIn[street] = std::unordered_map<PlayerId, int>();

    // At the start of every round, every player has put in no chips
    for (PlayerId playerId : playerIds) {
        amountsPutIn[street][playerId] = 0;
    }
}

void Pot::add(PlayerId playerId, int amount) {
    // Since startRound must have been called before this,
    // amountsPutIn[street][playerId] exists.
    amountsPutIn[street][playerId] += amount;
}

int Pot::amountBet(Street street, PlayerId playerId) {
    // Since startRound must have been called before this,
    // amountsPutIn[street][playerId] exists.
    return amountsPutIn[street][playerId];
}

std::unique_ptr<std::unordered_map<PlayerId, int>>
Pot::getWinnings(TableCards &tableCards, PlayersInHand &playersInHand) {

    // Splitting up winnings is challenging because not all players in the pot
    // may have contributed equally to it. For instance, if someone bets 100,
    // but another player has only 20 chips and goes all in and wins, we should
    // return their initial bet of 20 chips + the 20 chips they won in the hand.
    // The player that put in 100 chips still should retain 80 chips.

    // Our strategy is as follows: Split up the pot into smaller sized chunks,
    // where each of the players in the pot contributed equally to it.
    // In our example, we would have a sub-pot of 20 chips from each player.

    // Then, deal out the chips from this sub pot and remove those chips from
    // the pot. Now the pot is left with 80 chips from the first player.

    // Repeat this process until there are zero chips left in the pot: The next
    // sub-pot becomes the 80 chips from the first player, and the only one
    // playing for this sub pot is the original player.

    // Combine the pots from each street to make it easier to work with.
    std::unordered_map<PlayerId, int> combinedPot;
    for (auto it = amountsPutIn.begin(); it != amountsPutIn.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            combinedPot[it2->first] += it2->second;
        }
    }
    std::vector<PlayerId> playerIdsInHand =
        playersInHand.getPlayersStillInHand();

    // Initialize the winings of each player to 0.
    std::unique_ptr<std::unordered_map<PlayerId, int>> winnings =
        std::make_unique<std::unordered_map<PlayerId, int>>();
    for (PlayerId playerId : playerIdsInHand) {
        winnings->insert({playerId, 0});
    }

    // Tells us if the pot is empty.
    auto isEmpty = [&combinedPot]() {
        for (auto it = combinedPot.begin(); it != combinedPot.end(); it++) {
            if (it->second > 0) {
                return false;
            }
        }
        return true;
    };

    while (!isEmpty()) {
        // Find the smallest contribution to the pot. This tells us the
        // smallest sub-pot to play for.
        int smallestContribution = std::numeric_limits<int>::max();
        for (PlayerId playerId : playerIdsInHand) {
            if (combinedPot[playerId] > 0 &&
                combinedPot[playerId] < smallestContribution) {
                smallestContribution = combinedPot[playerId];
            }
        }

        // Figure out which players are playing in this pot. This is everyone in
        // the hand who has contributed to this pot
        std::vector<PlayerId> playersInPot;
        for (PlayerId playerId : playerIdsInHand) {
            // Technically we can check combinedPot[playerId] > 0, and they
            // would be equivalent, but this extra stringent check helps catch
            // potential implementation bugs.
            if (combinedPot[playerId] >= smallestContribution) {
                playersInPot.push_back(playerId);
            }
        }

        // Remove the sub-pot from future consideration. In the process we want
        // to figure out how much this pot is worth.
        // This pot is not just worth smallestContribution * number of players
        // in pot because it can also include contributions from players who
        // have folded out of the hand.
        int potAmt = 0;
        for (auto it = combinedPot.begin(); it != combinedPot.end(); it++) {
            if (it->second >= smallestContribution) {
                it->second -= smallestContribution;
                potAmt += smallestContribution;
            } else {
                it->second = 0;
                potAmt += it->second;
            }
        }

        // Distributed the winnings evenly amongst the winners.
        // Since chips are integral, this is perfect.
        std::vector<PlayerId> potWinners = tableCards.getWinners(playersInPot);
        int amountPerPerson = potAmt / potWinners.size();

        for (PlayerId playerId : potWinners) {
            winnings->at(playerId) += amountPerPerson;
        }
    }

    return winnings;
}
