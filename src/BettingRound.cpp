#include "BettingRound.h"
#include <cassert>

BettingRound::BettingRound() { m_currentBet = 0; }

void BettingRound::raiseTo(int amount) {
    // Raising must always increase the current bet
    assert(amount > m_currentBet);
    m_currentBet = amount;
}

void BettingRound::allInTo(int amount) {
    // If the allIn exceeds the current bet, then players must match the all in
    // to stay in the hand.
    if (amount > m_currentBet) {
        m_currentBet = amount;
    }
}

int BettingRound::currentBet() { return m_currentBet; }
