
# Introduction
This is a simulator and hand evaluator for texas holdem poker.  
Texas holdem explained: https://bicyclecards.com/how-to-play/texas-holdem-poker

# Simulating Poker Games

See `test/FullGameTest.cpp` for an example simulation of a game. See `include/Game.h` for a powerful interface which can be used to simulate any game.

# Evaluating Poker Hands

Figure out what each players chances are of winning a particular game: `TableCards::winningProbabilities`

Find out what your chances are of making a particular 5-card hand: `HoleCards::evaluatePotential`

Both use a monte-carlo simulation to quickly determine reasonably accurate probabilities.

# Coming Soon
Competetive poker website: Chess.com but for poker.

Trainer: Practice reading card ranges and exploiting suboptimal play.

Dataset: The most extensive poker dataset ever collected.

