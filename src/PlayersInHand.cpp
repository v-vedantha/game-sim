#include "PlayersInHand.h"
#include <iostream>

PlayersInHand::PlayersInHand(std::vector<PlayerId> playerIds) {
    this->playersInGame = playerIds;

    // Initially all players in the hand can bet
    // Technically players without chips cannot bet, but we don't worry about
    // that because they must eventually go "all in" or fold, and will thus be
    // removed from the betting pool.
    for (PlayerId playerId : playerIds) {
        playersWhoCanBet.insert(playerId);
    }
}

void PlayersInHand::startNewBettingRound() {
    // Eventually action will start on the dealer/blinds depending on which
    // street it is, but for now action starts on the first player in
    // playersInGame, and ends on the last player
    lastPlayer = playersInGame.size() - 1;
    currentPlayer = 0;
    m_isBettingOver = false;
}

void PlayersInHand::removeCurrentPlayerFromBetting() {
    playersWhoCanBet.erase(playersInGame[currentPlayer]);
}

void PlayersInHand::advanceCurrentPlayer() {
    // We want to skip over players who cannot bet, hence the while() loop.
    // The current player may have also gone all in, so they might not be able
    // to bet either, so we need to advance the current player by one no matter
    // what, hence the do-while.
    do {
        // If the last player has acted, then betting is over.
        if (currentPlayer == lastPlayer) {
            m_isBettingOver = true;
            break;
        }
        // If betting has not ended, advance the current player
        currentPlayer = (currentPlayer + 1) % playersInGame.size();
    } while (playersWhoCanBet.find(playersInGame[currentPlayer]) ==
                 playersWhoCanBet.end() &&
             playersWhoFolded.find(playersInGame[currentPlayer]) !=
                 playersWhoFolded.end()); // Skip over players who cannot bet,
                                          // and players who have folded
}

void PlayersInHand::everyoneCanAct() {
    // When everyone is allowed to act, the previous player is now the last one
    // who can act.
    // We dont need to worry about wether the previous player is allowed to bet,
    // since the advanceCurrentPlayer method takes care of skipping over players
    // who aren't allowed to bet.
    lastPlayer = currentPlayer - 1;
    if (lastPlayer < 0) {
        lastPlayer = playersInGame.size() - 1;
    }
}

PlayerId PlayersInHand::nextIdToAct() { return playersInGame[currentPlayer]; }

void PlayersInHand::removeCurrentPlayerFromHand() {
    playersWhoFolded.insert(playersInGame[currentPlayer]);
}

std::vector<PlayerId> PlayersInHand::getPlayersStillInHand() {
    // The players still in the hand is everyone in the game who has not folded
    // yet.
    std::vector<PlayerId> playersStillInHand;
    for (PlayerId player : playersInGame) {
        if (playersWhoFolded.find(player) == playersWhoFolded.end()) {
            playersStillInHand.push_back(player);
        }
    }
    return playersStillInHand;
}

bool PlayersInHand::isBettingOver() { return m_isBettingOver; }
