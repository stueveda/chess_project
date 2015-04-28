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
		int game_ply;

		MOVE_HISTORY history[MAXMOVES];
		

	public:

		bool getSide();
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
		void addQuietMove(int move, MOVE_LIST *list);
		void addCaptureMove(int move, MOVE_LIST *list);
		void addEnPassantMove(int move, MOVE_LIST *list);
		void addCapOrQuiet(int piece_type, int from, int to, bool side, MOVE_LIST *list);
		void generateAllMoves(MOVE_LIST *list);
		void addWPawnCapMove(const int from, const int to, const int cap, MOVE_LIST *list);
		void addWPawnMove(const int from, const int to, MOVE_LIST *list);
		void addBPawnCapMove(const int from, const int to, const int cap, MOVE_LIST *list);
		void addBPawnMove(const int from, const int to, MOVE_LIST *list);
		void deletePiece(const int sq);
		void addPiece(const int sq, const int piece_type);
		void movePiece(const int from, const int to);
		bool makeMove(int move);
		void undoMove();
		void printMoveList(MOVE_LIST *list);

		int parseMove(char *c_ptr);

		long perft(int depth);
		long perftTest(int depth);

		std::string getFEN();
		int parseFEN(const char *fen);
};

#endif