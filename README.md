
# Introduction
This is a simulator and hand evaluator for texas holdem poker.  
Texas holdem explained: https://bicyclecards.com/how-to-play/texas-holdem-poker

# Simulating Poker Games

See `test/FullGameTest.cpp` for an example simulation of a game.

# Evaluating Poker Hands

Figure out what each players chances are of winning a particular game: `TableCards.h:winningProbabilities`

Find out what your chances are of making a particular hand: `HoleCards:evaluatePotential`

Both use a monte-carlo simulation to quickly determine reasonably accurate probabilities.

# Future Features
Poker ranges: Figure out what an opponents odds are of making a hand given their range.

Free competetive poker website: Chess.com but for poker.

Trainer: Practice reading card ranges and exploiting suboptimal play.

Dataset: The most extensive poker dataset ever collected.

