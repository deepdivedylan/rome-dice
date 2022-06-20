# Rome: Pathway to Power Dice Game 🎲

This is a fun simulation of the dice mini game in _Rome: Pathway to Power_, a game distributed by Maxis circa 1992. The game is played thusly:

1. Bet 4.
2. Roll dice.
    * If roll is a 6, win 14 (net win of 10).
    * If roll is 4 or 5, win 4 (net win of 0).
    * If roll is 1, 2, or 3, lose.

The expected value is (⅙ × 10) + (⅓ × 0) + (½ × -4) = -⅓. Obviously, the players will lose their money very fast. So, this program sets up a nihilstic tournament that tracks how long the players survive. Each player is forced to play until they run out of money. The player to survive the longest wins.

# Usage

Compile the program using any C compiler and execute it. With no arguments, it will prompt for the names from `stdin`. Adding another argument will read each player's name, line by line. For instance, create a simple text file named `players.txt` and fill it with names:

```
Jean-Luc
Will
Deanna
Geordi
Beverly
```

Then execute `rome-dice players.txt` and watch the fun begin.

# Future Work

This was coded late at night just to prank my coworkers. It's very imperfect code without a lot of thought. The memory management could be refactored to be easier. I should add a way to configure different run time variables. If you have better ideas, I eagerly await your pull requests.
