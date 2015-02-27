// file:			board.cpp
// author:			Dan Stueve
// date:			2/7/2015
// last modified:	2/23/2015

// this file contains the specification of the Board class.

#include <iostream>

/*
We'll be using an unsigned 64-bit integer (Referred to as U64 throughout
the code) for many different aspects of board representation. Because there
are 64 squares on a chess board, a U64 acts as a sort of incidence matrix
for piece existence on the board.
*/
typedef unsigned long long U64;


/*
For almost all aspects of the Board, class members and functions will be
prefixed with W or B, meaning the white or black pieces, respectively.
*/
class Board
{
	private:

		U64 w_pawns;
		U64 w_knights;
		U64 w_bishops;
		U64 w_rooks;
		U64 w_queens;
		U64 w_kings;

		U64 b_pawns;
		U64 b_knights;
		U64 b_bishops;
		U64 b_rooks;
		U64 b_queens;
		U64 b_kings;

	public:
		/**************** GET WHITE OPERATIONS *************/
		U64 getWPawns();
		U64 getWKnights();
		U64 getWBishops();
		U64 getWRooks();
		U64 getWQueens();
		U64 getWKings();

		U64 getWPawnsAttack();
		U64 getWKnightsAttack();
		U64 getWBishopsAttack();
		U64 getWRooksAttack();
		U64 getWQueensAttack();
		U64 getWKingsAttack();

		/**************** GET BLACK OPERATIONS ***************/
		U64 getBPawns();
		U64 getBKnights();
		U64 getBBishops();
		U64 getBRooks();
		U64 getBQueens();
		U64 getBKings();

		U64 getBPawnsAttack();
		U64 getBKnightsAttack();
		U64 getBBishopsAttack();
		U64 getBRooksAttack();
		U64 getBQueensAttack();
		U64 getBKingsAttack();

		/****************** GET GENERAL OPERATIONS ******************/
		U64 getWPieces();
		U64 getBPieces();
		U64 getAllPieces();

		/****************** SET WHITE OPERATIONS *******************/
		void setWPawns(U64 n);
		void setWKnights(U64 n);
		void setWBishops(U64 n);
		void setWRooks(U64 n);
		void setWQueens(U64 n);
		void setWKings(U64 n);

		/**************** SET BLACK OPERATIONS ***************/
		void setBPawns(U64 n);
		void setBKnights(U64 n);
		void setBBishops(U64 n);
		void setBRooks(U64 n);
		void setBQueens(U64 n);
		void setBKings(U64 n);

		/************ SET GENERAL OPERATIONS ***********/
		void setInitialPosition();
};
