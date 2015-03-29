// file:			board.cpp
// author:			Dan Stueve


// this file contains the specification of the Board class.

#ifndef BOARD_H
#define BOARD_H

#include "defs.h"


/*
For almost all aspects of the Board, class members and functions will be
prefixed with W or B, meaning the white or black pieces, respectively.
*/
class Board
{
	private:
		U64 bitboardArray[13];

		bool w_king_castle;
		bool w_queen_castle;
		bool b_king_castle;
		bool b_queen_castle;

		int ep_square;

		bool side_to_move;
		int ply;

		MOVE_HISTORY history[MAXMOVES];
		MOVE_LIST move_list[MAXPOSITIONMOVES];

	public:
		U64 getPieceBitboard(int piece_type);
		void setPieceBitboard(int piece_type, U64 bb);
		U64 getWPieces();
		U64 getBPieces();
		U64 getAllPieces();
		U64 getEmpty();
		int getPieceType(int sq);
		bool isSqAttacked(const int sq, const bool side);

		void clearBoard();
		void setInitial();
		void printBoard();
		void printAttacked(const bool side);

		// move generator functions
		void addQuietMove(int move);
		void addCaptureMove(int move);
		void addEnPassantMove(int move);
		void addCapOrQuiet(int piece_type, int from, int to, bool side);
		void generateAllMoves();
		void addWPawnCapMove(const int from, const int to, const int cap);
		void addWPawnMove(const int from, const int to);
		void addBPawnCapMove(const int from, const int to, const int cap);
		void addBPawnMove(const int from, const int to);
		void printMoveList();

		int parseFEN(char *fen);
};

#endif