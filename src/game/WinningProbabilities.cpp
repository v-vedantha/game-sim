#include "WinningProbabilities.h"
#include <cassert>
#include <map>

WinningProbabilities::WinningProbabilities(
    std::unique_ptr<std::unordered_map<PlayerId, double>>
        winningProbabilities) {
    // We should probably validate the winning probabilities are in the range
    // 0-1 and sum to 1.0.
    this->winningProbabilities = std::move(winningProbabilities);
}

double WinningProbabilities::getProbabilityOfWinning(PlayerId player) {
    return winningProbabilities->at(player);
}

WinningProbabilitiesBuilder::WinningProbabilitiesBuilder(
    std::vector<PlayerId> players) {
    // Initially none of the players have won any runouts.
    for (const PlayerId &player : players) {
        this->winningRunouts[player] = 0;
    }
}

void WinningProbabilitiesBuilder::addRunoutResult(
    const std::vector<PlayerId> &winners) {
    assert(winners.size() > 0);
    // Each of the N winners gets credit for 1/N runouts. In most cases
    // there is only one winner. There is never 0-winners (in a tie all tied
    // people win)
    for (const PlayerId &player : winners) {
        this->winningRunouts[player] += 1.0 / winners.size();
    }
}

WinningProbabilities WinningProbabilitiesBuilder::winningProbabilities() {
    std::unique_ptr<std::unordered_map<PlayerId, double>> winningProbabilities =
        std::make_unique<std::unordered_map<PlayerId, double>>();
    double totalRunouts = 0.0;
    for (auto it = this->winningRunouts.begin();
         it != this->winningRunouts.end(); it++) {
        totalRunouts += it->second;
    }

    // Just to sanity check that users remembered to add runouts and avoids
    // division by zero errors.
    assert(totalRunouts > 0.01);

    // The chance each player has of winning is the # of runouts they win / the
    // total number of runouts simulated.
    for (auto it = this->winningRunouts.begin();
         it != this->winningRunouts.end(); it++) {
        winningProbabilities->insert({it->first, it->second / totalRunouts});
    }

    return WinningProbabilities(std::move(winningProbabilities));
}
