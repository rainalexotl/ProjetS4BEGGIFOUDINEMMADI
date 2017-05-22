Hex Game Project
================

This project was assigned to the second year Computer Science students of Université Paul Sabatier. The task was to implement the Hex Game (a strategy board game played between two players on a hexagonal grid). The game was to be implemented in C (for the calculations) and in Java (for the interface)

![alt text](https://upload.wikimedia.org/wikipedia/commons/3/38/Hex-board-11x11-%282%29.jpg "Red and Blue Hex Game")

Our implementation includes the following functionnalities:
* Choose the board size
* Choose the player who will play first
* Blocks illegal moves
* Manages each player's turn
* Detects a winner
* Allows the players to quit with or without saving their game
* Manages the history of previously saved games
* Undo a move
* Save a game, restore a game, forfeit a game

Compilation Instructions
------------------------
In the `InterfaceAvecC.java` file in the code/codeJava/ directory, the library path must be modified. Thus the library must be generated according to your operationg system.

```javascript
static {
  System.load("absolute/library/path");
}
```

* To test and/or execute you must be in the project root.
* To test the modules type: `make TESTMODULE`
* To test the units type: `make TESTUNITAIRE`
* To test the Artificial Intelligence (game against the computer): `make TESTIA`
__(attention: the AI mode does not test if a move is illegal or not)__
* To play the game against a human: `make JAVA`
