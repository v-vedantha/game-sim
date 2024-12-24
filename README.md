# Texas Hold'em Poker Simulator and Hand Evaluator

This repository provides a simulator and hand evaluator for Texas Hold'em poker. Whether you're a poker enthusiast, a game developer, or a researcher, this tool allows you to simulate games, evaluate hands, and calculate probabilities.

**Learn Texas Hold'em**: [Official Bicycle Cards Guide](https://bicyclecards.com/how-to-play/texas-holdem-poker)

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


##  Usage

This project uses cmake and c++20

Clone the project ```git clone https://github.com/v-vedantha/game-sim.git``` and run the tests via ```./test.sh```
