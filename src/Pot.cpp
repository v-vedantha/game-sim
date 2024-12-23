#include "Pot.h"
#include <iostream>

Pot::Pot(std::vector<PlayerId> playerIds) {
    for (PlayerId playerId : playerIds) {
        amountsPutIn[street][playerId] = 0;
    }
}

void Pot::startRound(Street street) {
    this->street = street;
    amountsPutIn[street] = std::unordered_map<PlayerId, int>();
}

void Pot::add(PlayerId playerId, int amount) {
    amountsPutIn[street][playerId] += amount;
}

int Pot::amountBet(Street street, PlayerId playerId) {
    return amountsPutIn[street][playerId];
}

std::unique_ptr<std::unordered_map<PlayerId, int>>
Pot::getWinnings(TableCards &tableCards, PlayersInHand &playersInHand) {

    std::unordered_map<PlayerId, int> combinedPot;
    for (auto it = amountsPutIn.begin(); it != amountsPutIn.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            combinedPot[it2->first] += it2->second;
        }
    }
    std::vector<PlayerId> playerIdsInHand =
        playersInHand.getPlayersStillInHand();

    std::unique_ptr<std::unordered_map<PlayerId, int>> winnings =
        std::make_unique<std::unordered_map<PlayerId, int>>();
    for (PlayerId playerId : playerIdsInHand) {
        winnings->insert({playerId, 0});
    }

    auto isEmpty = [&combinedPot]() {
        for (auto it = combinedPot.begin(); it != combinedPot.end(); it++) {
            if (it->second > 0) {
                return false;
            }
        }
        return true;
    };

    while (!isEmpty()) {
        // Of all the players still in the hand, the smallest non-zero
        // contribution defines the size of the sub-pot everyone is playing for
        int smallestContribution = std::numeric_limits<int>::max();
        for (PlayerId playerId : playerIdsInHand) {
            if (combinedPot[playerId] > 0 &&
                combinedPot[playerId] < smallestContribution) {
                smallestContribution = combinedPot[playerId];
            }
        }

        // The players who play for this pot is everyone in the hand who has
        // contributed to this pot
        std::vector<PlayerId> playersInPot;
        for (PlayerId playerId : playerIdsInHand) {
            if (combinedPot[playerId] >= smallestContribution) {
                playersInPot.push_back(playerId);
            }
        }

        // Remove this sub-pot
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

        // Get the winners
        std::vector<PlayerId> potWinners = tableCards.getWinners(playersInPot);

        // The amount each person gets is the pot divided by the number of
        // winners
        int amountPerPerson = potAmt / potWinners.size();

        for (PlayerId playerId : potWinners) {
            winnings->at(playerId) += amountPerPerson;
        }
    }

    return winnings;
}
