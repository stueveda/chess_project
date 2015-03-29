// file:			main.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// This file contains the main program that runs the chess game

#include <iostream>
#include <string>
#include "defs.h"
#include "board.h"
using std::string;

// for testing parseFEN
#define FEN0 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"
#define FENTEST "4k2r/8/8/8/8/8/8/R3K2R B KQkq - 1 1"
#define FENTEST2 "rnbqkbnr/p1p1p3/3p3p/1p1p4/2P1Pp2/8/PP1P1PpP/RNBQKB1R b KQkq e3 0 1"


int main()
{
	// initialize the board
	Board b;

	// read in the FEN for the starting position
	b.parseFEN(FENTEST);
	// print it to the screen
	b.printBoard();
	std::cout<< "\n\n";

	b.generateAllMoves();
	b.printMoveList();
	
	std::cin.ignore();
	return 0;
}