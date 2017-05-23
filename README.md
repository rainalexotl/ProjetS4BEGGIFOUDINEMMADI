Hex Game Project
================

This project was assigned to the second year Computer Science students of Université Paul Sabatier. The task was to implement the Hex Game (a strategy board game played between two players on a hexagonal grid). The game was to be implemented in C (for the calculations) and in Java (for the interface). All the documents to turn in for the project are in the doc directory.

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
In the `InterfaceAvecC.java` file in the ProjetS4BEGGIFOUDINEMMADI/code/codeJava/ directory, the library path must be modified. Thus the library must be generated according to your operationg system.

To generate the library change your working directory to ProjetS4BEGGIFOUDINEMMADI/lib/ and execute the following commands

#### For Linux:
```
$ gcc -I/usr/java/jdk1.5.0_01/include/
      -I/usr/java/jdk1.5.0_01/include/linux -c -fPIC InterfaceAvecC.c
$ gcc -shared -o libInterfaceAvecC.so InterfaceAvecC.o
```

#### For Mac:
```
$ gcc -I/Library/Java/Home/include/
      -I/Library/Java/Home/include/darwin -c InterfaceAvecC.c
$ gcc -shared -o libInterfaceAvecC.dylib InterfaceAvecC.o
```

#### For Windows
```
$ gcc -c -I"C:\j2sdk1.4.2_02\include"
         -I"C:\j2sdk1.4.2_02\include\win32"
         -o InterfaceAvecC.o TestJNI2.c
$ gcc -shared -o InterfaceAvecC.dll InterfaceAvecC.c InterfaceAvecC.c InterfaceAvecC.def
```

#### For solaris
```
$ cc -G -I/opt/JAVA/jdk1.5.0_01/include -I/opt/JAVA/jdk1.5.0_01/include/solaris InterfaceAvecC.c
     -o libInterfaceAvecC.so
```
     
__!__ of course the java paths will vary depending on your installation

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