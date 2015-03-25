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
#define FENTEST "8/3q1p2/8/5P2/4Q3/8/8/8 w - - 0 1"


int main()
{
	// initialize the board
	Board b;

	// read in the FEN for the starting position
	b.parseFEN(FEN0);
	// print it to the screen
	b.printBoard();
	std::cout<< "\n\n";

	std::cout << "white attacks:\n";
	b.printAttacked(WHITE);

	std::cout << "black attacks:\n";
	b.printAttacked(BLACK);
	/*
	for (int i = 0; i < 64; i++)
	{
		if (b.isSqAttacked(i, WHITE))
			std::cout << i << " is attacked by white.\n";
	}
	for (int i = 0; i < 64; i++)
	{
		if (b.isSqAttacked(i, BLACK))
			std::cout << i << " is attacked by black.\n";
	}
	// read the position after 1. e4
	b.parseFEN(FEN1);
	b.printBoard();
	std::cout<< "\n\n";
	for (int i = 0; i < 64; i++)
	{
		if (b.isSqAttacked(i, WHITE))
			std::cout << i << " is attacked by white.\n";
	}

	// read the position after 1...c5
	b.parseFEN(FEN2);
	b.printBoard();
	std::cout<< "\n\n";
	for (int i = 0; i < 64; i++)
	{
		if (b.isSqAttacked(i, WHITE))
			std::cout << i << " is attacked by white.\n";
	}

	// read the position after 2. Nf3
	b.parseFEN(FEN3);
	b.printBoard();
	std::cout<< "\n\n";
	for (int i = 0; i < 64; i++)
	{
		if (b.isSqAttacked(i, WHITE))
			std::cout << i << " is attacked by white.\n";
	}
	*/
	std::cin.ignore();
	return 0;
}