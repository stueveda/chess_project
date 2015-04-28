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

#define FENTEST "2r1r3/3b1k2/2p1pn2/ppN3q1/1p6/1P1P1P2/P3PQ1P/1KR2R2 b -"


int main()
{
	std::cout << "Chess Engine by Dan Stueve\n\n";

	Board b;
	b.setInitial();
	string input;
	b.printBoard();
	std::cout << "\ncommand: ";
	std::cin >> input;
	while (input != "exit")
	{
		MOVE_LIST move_list[1];
		b.generateAllMoves(move_list);
		if (input == "printboard")
		{
			b.printBoard();
		}
		else if (input == "save")
		{
			std::ofstream file;
			file.open("savegame.txt");
			file << b.getFEN();
			file.close();
			std::cout << b.getFEN() << "\n";
			std::cout << "saved game FEN to 'savegame.txt'\n";
		}
		else if (input == "load")
		{
			string fen;
			std::ifstream file;
			file.open("savegame.txt");
			std::getline(file,fen);
			const char* c_fen = fen.c_str();
			b.parseFEN(c_fen);
			std::cout << "Loaded game from 'savegame.txt'\n";
		}
		else if (input == "undo")
		{
			b.undoMove();
		}
		else if (input == "newgame")
		{
			b.setInitial();
		}
		else if (input == "help")
		{
			std::cout << "To move, type starting square and ending square in format:\n";
			std::cout << "e2e4\n\n";
			std::cout << "printboard - prints the board state.\n\n";
			std::cout << "save - saves an FEN of the current game to 'savegame.txt'.\n\n";
			std::cout << "load - loads the FEN from 'savegame.txt'.\n\n";
			std::cout << "undo - undoes the last move.\n\n";
			std::cout << "newgame - starts a new game at the initial board position,\n\n";
			std::cout << "exit - quits the program.\n\n";
		}
		else if ((input.length() == 4 || input.length() == 5) &&
				input[0] >= 'a' && input[0] <= 'h' &&
				input[1] >= '1' && input[1] <= '8' &&
				input[2] >= 'a' && input[2] <= 'h' &&
				input[3] >= '1' && input[3] <= '8')
		{
			int prom = 0;
			int from = (input[0] - 'a' + (input[1] - '1') * 8);
			int to = (input[2] - 'a' + (input[3] - '1') * 8);
			if (input.length() == 5)
			{
				if (b.getSide() == WHITE)
				{
					if (input[4] == 'q')
					{
						prom = wQ;
					}
					else if (input[4] == 'r')
					{
						prom = wR;
					}
					else if (input[4] == 'b')
					{
						prom = wB;
					}
					else if (input[4] == 'n')
					{
						prom = wN;
					}
				}
				else
				{
					if (input[4] == 'q')
					{
						prom = bQ;
					}
					else if (input[4] == 'r')
					{
						prom = bR;
					}
					else if (input[4] == 'b')
					{
						prom = bB;
					}
					else if (input[4] == 'n')
					{
						prom = bN;
					}
				}
			}

			bool found = false;
			for (int i = 0; i < move_list->count; i++)
			{
				int move = move_list->moves[i].move;
				if (FROMSQ(move) == from &&
					TOSQ(move) == to &&
					PROM_PIECE(move) == prom)
				{
					if (!b.makeMove(move))
					{
						std::cout << "not a legal move\n\n";
					}
					else
					{
						std::cout << "making move ";
						printMove(move);
						std::cout << "\n";
					}
					found = true;
					break;
				}
			}
			if (!found)
			{
				std::cout << "not a legal move.\n\n";
			}

			if (b.perft(1) == 0)
			{
				std::cout << "Checkmate!\n\n";
			}
		}
		else
		{
			std::cout << "command not recognized\n\n";
		}
		std::cout << "\ncommand: ";
		std::cin >> input;
	}
	return 0;
}