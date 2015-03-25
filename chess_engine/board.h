// file:			board.cpp
// author:			Dan Stueve


// this file contains the specification of the Board class.

#ifndef BOARD_H
#define BOARD_H

#include "defs.h"


enum 
{
	wP, wN, wB, wR, wQ, wK,
	bP, bN, bB, bR, bQ, bK
};

/*
For almost all aspects of the Board, class members and functions will be
prefixed with W or B, meaning the white or black pieces, respectively.
*/
class Board
{
	private:
		U64 bitboardArray[12];

		bool w_king_castle;
		bool w_queen_castle;
		bool b_king_castle;
		bool b_queen_castle;

		int ep_square;

		bool side_to_move;
		int ply;

		MOVE_HISTORY history[MAXMOVES];

	public:
		U64 getPieceBitboard(int piece_type);
		void setPieceBitboard(int piece_type, U64 bb);
		U64 getWPieces();
		U64 getBPieces();
		U64 getAllPieces();
		bool isSqAttacked(const int sq, const bool side);

		void clearBoard();
		void setInitial();
		void printBoard();
		void printAttacked(const bool side);


		int parseFEN(char *fen);
};

#endif