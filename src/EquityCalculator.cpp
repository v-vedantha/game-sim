#include "EquityCalculator.h"
#include "HandRanker.h"

class OddsBuilder {

    std::vector<std::array<Card, 2>> playersHands;
    std::vector<Card> board;
    Deck deck;

    std::vector<int> playerWins;


public:
    OddsBuilder(std::vector<std::array<Card, 2>> playersHands, std::vector<Card> board, Deck deck) {
        this->playersHands = playersHands;
        this->board = board;
        this->playerWins = std::vector<int>(playersHands.size(), 0);
    }

    TableOdds buildEquity() {
        for (std::vector<Card> runout : deck.getRunouts(5 - board.size())) {

            std::vector<Card> board_copy = board;
            for (Card& card : runout) {
                board_copy.push_back(card);
            }

            Winner handWinner = getWinner(playersHands, board_copy);

            if (handWinner.hasWinner) {
                playerWins[handWinner.winner]++;
            }
        }
    }
}

TableOdds calculateEquity(std::vector<std::array<Card, 2>> playersHands, std::vector<Card> muck, std::vector<Card> board) {
    Deck deck;
    for (Card& card : muck) {
        deck.removeCard(card);
    }

    for (Card& card : board) {
        deck.removeCard(card);
    }

    for (std::array<Card, 2>& hiddenCards : playersHands) {
        deck.removeCard(hiddenCards.getCards()[0]);
        deck.removeCard(hiddenCards.getCards()[1]);
    }

    EquityBuilder equityBuilder(playersHands, board, deck);

    return equityBuilder.buildEquity();
}
