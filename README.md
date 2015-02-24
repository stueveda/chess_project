#Chess Engine
###Description
A chess engine implemented in C++.
Created By Dan Stueve.

###Board Representation
Representation of the chess board and piece positions is done through bitboards. You can read more about bitboards
[here](https://chessprogramming.wikispaces.com/Board+Representation).

####board.h
Contains the specification of the Board class.

####board.cpp
Contains the implementation of the Board class.

Has functions to:

* get position of all pieces of a certain type and color
* get position of all pieces of a certain color
* get position of all pieces
* set position of all pieces of a certain type and color
* set the initial position of the board
* print an incidence matrix of a position (for debugging)

###main.cpp
Contains the main calling function. Will be used to run the chess
program upon completion, but in the meantime will act as a means of
	testing and debugging.