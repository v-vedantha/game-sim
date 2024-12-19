

class BettingRound {

public:
    BettingRound();

    void raiseTo(int amount);
    void allIn(int amount);

    int currentBet();

private:
    int m_currentBet;
};
