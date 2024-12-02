#include "Card.h"
#include "HandEvaluator.h"
#include <array>

typedef struct {
    bool hasWinner;
    int winnerIdx;
} Winner;

Winner getWinner(const std::vector<std::array<Card, 2>>& hands, const std::array<Card, 5>& board);

HandEvaluation bestEvaluation(const std::array<Card, 2>& hiddenCards, const std::array<Card, 5>& board);
