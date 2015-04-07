// file:			main.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// This file contains the main program that runs the chess game

#include <iostream>
#include <fstream>
#include <string>
#include "defs.h"
#include "board.h"
using std::string;

// for testing parseFEN
#define FEN0 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"

#define FENTEST "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"


int main()
{
	// initialize the board
	Board b;
	b.parseFEN(FENTEST);
	b.printBoard();
	int num = 5;
	
	std::cout << b.perftTest(num) << "\n";

	/*
	string line;
	std::ifstream myfile;
	std::ofstream outfile;
	myfile.open("perft.txt");
	outfile.open("output.txt");
	while (std::getline(myfile, line))
	{
		const char *fen = line.c_str();
		b.parseFEN(fen);
		outfile << b.perft(num) << "\n";
		std::cout << b.perft(num) << "\n";
	}
	*/

	
	/*
	
	MOVE_LIST move_list[1];
	MOVE_LIST move_list2[1];
	std::cout<< "\n\n";
	b.generateAllMoves(move_list);

	
	int move = 0;
	for (int i = 0; i < move_list->count; i++)
	{
		std::cout << "move_num = " << i << "\n";
		move = move_list->moves[i].move;
		if (!b.makeMove(move))
		{
			std::cout << "not legal\n";
			continue;
		}


		std::cout << "initial move: ";
		printMove(move);
		std::cout << "\n";
		b.printBoard();
		std::cin.ignore();
		
		
		std::cout << "REPLY MOVES\n";

		b.generateAllMoves(move_list2);

		for (int j = 0; j < move_list2->count; j++)
		{
			std::cout << "move_num = " << j << "\n";
			move = move_list2->moves[j].move;
			if (!b.makeMove(move))
			{
				printMove(move);
				std::cout << " is not legal\n\n";
				continue;
			}
			std::cout << "made move: ";
			printMove(move);
			std::cout << "\n";
			b.printBoard();
			b.undoMove();
			std::cin.ignore();
		}
		
		b.undoMove();
		std::cout << "\n";
		
	}
	*/
	std::cin.ignore();
	return 0;
}