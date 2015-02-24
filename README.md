# chess_project
Created by: Dan Stueve
Started 1/25/2015
C++ Chess Engine

board.h
	contains the specification of the Board class. See more
	[here](https://chessprogramming.wikispaces.com/Board+Representation)
	for a more detailed explanation of bitboards.
	
board.cpp
	contains the implementation of the Board class.
	Has functions to:
		- get position of all pieces of a certain type and color
		- get position of all pieces of a certain color
		- get position of all pieces
		- set position of all pieces of a certain type and color
		- set the initial position of the board
		- print an incidence matrix of a position (for debugging)

main.cpp
	contains the main calling function. Will be used to run the chess
	program upon completion, but in the meantime will act as a means of
	testing and debugging.