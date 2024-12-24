# Texas Hold'em Poker Simulator and Hand Evaluator

This repository provides a simulator and hand evaluator for Texas Hold'em poker. Whether you're a poker enthusiast, a game developer, or a researcher, this tool allows you to simulate games, evaluate hands, and calculate probabilities.

**Learn Texas Hold'em**: [Official Bicycle Cards Guide](https://bicyclecards.com/how-to-play/texas-holdem-poker)

---
## Terminology
- Suit: Spades, Clubs, Hearts, Diamons
- Value: The value of a card. 2-10, J-A
- HoleCards: The two cards that each player has. Not visible to other players
- Board: Up to 5 community cards everyone can see and use to construct a hand
- Deck: The deck of cards
- Runout: In the context of simulating a runout, this means simulating what would happen if some random cards were dealt.
- Pot: The money people have bet
- Call,Fold,Raise,Check: The usual poker actions
- TableCards: The cards on the table (i.e. all the cards in a game)
- Hand: 5 cards you can construct using your two hole cards and the board.
- Rank of a hand/Primary hand: Royal flush, Pair, Quads etc.
- Strength: How strong a hand is. Strengths can be compared. Rank + kickers. 
- Kickers: When two hands with the same rank are compared, they could still differ in kickers. For example, an Ace high flush beats a king high flush becase the Ace kicker beats the King. This is slightly different from the usual definition because kickers includes the cards that make up the primary hand
- Street: Preflop, Flop, Turn, River. Streets tell you how many cards are dealt to the board. On the flop there are 3, turn has 4, and river has 5. 
- Round: Somewhat similar to street. Used mostly interchangably.
- Potential: The potential of a hand is the hands you might make if the correct cards are dealt to the board. Only makes sense if the board still has more cards to be dealt. 
---

## Features

### Simulating Poker Games
- **Game Simulation**: Fully simulate poker games using a flexible API.
  - **Example**: See `test/FullGameTest.cpp` for a complete simulation of a Texas Hold'em game.
  - **Interface**: Use `include/Game.h` to define and run custom game scenarios.

### Evaluating Poker Hands
- **Winning Probability**:
  - Calculate each player's chances of winning a particular game with `TableCards::winningProbabilities`.
- **Hand Potential**:
  - Determine your chances of making a specific 5-card hand using `HoleCards::evaluatePotential`.
- **Fast and Efficient**: Both methods use Monte Carlo simulations for quick and reasonably accurate results.

---

## Repository Structure

- **`include/`**: Core headers for simulating games and evaluating hands.
  - `Game.h`: Main interface for defining and simulating poker games.
  - `HoleCards.h`: Utilities for evaluating the potential of specific hole cards.
  - `TableCards.h`: Functions for determining winning probabilities at the table.
- **`src/`**: Source files implementing simulation and evaluation logic.
- **`test/`**: Examples and unit tests to demonstrate functionality.
  - `FullGameTest.cpp`: Full simulation of a poker game.
  - `HandPotentialTest.cpp`: Example usage of `HoleCards::evaluatePotential`


##  Usage

This project uses cmake and c++20

Clone the project ```git clone https://github.com/v-vedantha/game-sim.git``` and run the tests via ```./test.sh```
