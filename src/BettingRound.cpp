#include "BettingRound.h"
#include <cassert>

BettingRound::BettingRound() { m_currentBet = 0; }

void BettingRound::raiseTo(int amount) {
    assert(amount > m_currentBet);
    m_currentBet = amount;
}

void BettingRound::allInTo(int amount) {
    if (amount > m_currentBet) {
        m_currentBet = amount;
    }
}

int BettingRound::currentBet() { return m_currentBet; }
